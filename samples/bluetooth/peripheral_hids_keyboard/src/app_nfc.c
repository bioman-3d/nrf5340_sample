/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#if CONFIG_NFC_OOB_PAIRING

#include "app_nfc.h"
#include <nfc_t2t_lib.h>

static struct bt_le_oob oob_local;
static u8_t ndef_msg_buf[256]; /* Buffer used to hold an NFC NDEF message. */

void nfc_field_detected(void);
void nfc_field_lost(void);

static void nfc_callback(void *context,
			 enum nfc_t2t_event event,
			 const u8_t *data,
			 size_t data_length)
{
	ARG_UNUSED(context);
	ARG_UNUSED(data);
	ARG_UNUSED(data_length);

	switch (event) {
	case NFC_T2T_EVENT_FIELD_ON:
		nfc_field_detected();
		break;
	case NFC_T2T_EVENT_FIELD_OFF:
		nfc_field_lost();
		break;
	default:
		break;
	}
}

int nfc_ndef_le_oob_msg_encode(u8_t *buffer, u32_t *len)
{
	int err;
	struct nfc_ndef_le_oob_rec_payload_desc rec_payload_desc;

	err = bt_le_oob_get_local(BT_ID_DEFAULT, &oob_local);
	if (err) {
		printk("Error while fetching local OOB data: %d\n", err);
	}

	memset(&rec_payload_desc, 0, sizeof(rec_payload_desc));
	rec_payload_desc.oob_data = &oob_local;
	rec_payload_desc.le_role = NFC_NDEF_LE_OOB_REC_LE_ROLE_PERIPH_ONLY;
	rec_payload_desc.include.local_name = true;
	rec_payload_desc.include.appearance = true;
	rec_payload_desc.include.le_sc_data = true;
	rec_payload_desc.include.flags = true;
	rec_payload_desc.flags = BT_LE_AD_NO_BREDR;

	/* Create NFC NDEF message description, capacity - 1 record */
	NFC_NDEF_MSG_DEF(nfc_le_oob_msg, 1);

	/* Create NFC NDEF LE OOB Record description without record ID field */
	NFC_NDEF_LE_OOB_RECORD_DESC_DEF(nfc_le_oob_rec, 0, &rec_payload_desc);

	/* Add LE OOB Record as lone record to message */
	err = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_le_oob_msg),
			&NFC_NDEF_LE_OOB_RECORD_DESC(nfc_le_oob_rec));
	if (err < 0) {
		printk("Error while adding LE OOB record: %d\n", err);
		return err;
	}

	err = nfc_ndef_msg_encode(&NFC_NDEF_MSG(nfc_le_oob_msg),
				      buffer,
				      len);
	if (err < 0) {
		printk("Error during NDEF message encoding: %d\n", err);
		return err;
	}

	return 0;
}

void app_nfc_init(void)
{
	u32_t len = sizeof(ndef_msg_buf);

	printk("NFC configuration start\n");

	/* Set up NFC */
	if (nfc_t2t_setup(nfc_callback, NULL) < 0) {
		printk("Cannot setup NFC T2T library!\n");
	}

	/* Prepare an NDEF message with LE OOB record. */
	if (nfc_ndef_le_oob_msg_encode(ndef_msg_buf, &len) < 0) {
		printk("Cannot encode BLE pair message!\n");
	}

	/* Set created message as the NFC payload */
	if (nfc_t2t_payload_set(ndef_msg_buf, len) < 0) {
		printk("Cannot set payload!\n");
	}

	/* Start sensing NFC field */
	if (nfc_t2t_emulation_start() < 0) {
		printk("Cannot start emulation!\n");
	}

	printk("NFC configuration done\n");
}

struct bt_le_oob *app_nfc_oob_data_get(void)
{
	return &oob_local;
}

#endif
