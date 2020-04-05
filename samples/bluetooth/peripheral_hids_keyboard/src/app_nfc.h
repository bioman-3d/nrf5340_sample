/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <nfc/ndef/nfc_ndef_msg.h>
#include <nfc/ndef/nfc_uri_msg.h>
#include <nfc/ndef/le_oob_rec.h>

/** @brief Initialize NFC.
 */
void app_nfc_init(void);

/** @brief Retrieve Out of Band data.
 */
struct bt_le_oob *app_nfc_oob_data_get(void);
