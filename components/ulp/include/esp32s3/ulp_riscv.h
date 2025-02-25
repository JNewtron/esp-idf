// /*
//  * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
//  *
//  * SPDX-License-Identifier: Apache-2.0
//  */

// #pragma once
// #include <stdint.h>
// #include <stddef.h>
// #include <stdlib.h>
// #include "esp_err.h"
// #include "ulp_common.h"

// #ifdef __cplusplus
// extern "C" {
// #endif

// /**
//  * @brief Run the program loaded into RTC memory
//  * @return  ESP_OK on success
//  */
// esp_err_t ulp_riscv_run(void);

// /**
//  * @brief Load ULP-RISC-V program binary into RTC memory
//  *
//  * Different than ULP FSM, the binary program has no special format, it is the ELF
//  * file generated by RISC-V toolchain converted to binary format using objcopy.
//  *
//  * Linker script in components/ulp/ld/esp32s3.ulp.riscv.ld produces ELF files which
//  * correspond to this format. This linker script produces binaries with load_addr == 0.
//  *
//  * @param program_binary pointer to program binary
//  * @param program_size_bytes size of the program binary
//  * @return
//  *      - ESP_OK on success
//  *      - ESP_ERR_INVALID_SIZE if program_size_bytes is more than 8KiB
//  */
// esp_err_t ulp_riscv_load_binary(const uint8_t* program_binary, size_t program_size_bytes);

// #ifdef __cplusplus
// }
// #endif

/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "esp_err.h"
#include "ulp_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ULP_RISCV_WAKEUP_SOURCE_TIMER,
    ULP_RISCV_WAKEUP_SOURCE_GPIO,
} ulp_riscv_wakeup_source_t;

/**
 * @brief ULP riscv init parameters
 *
 */
typedef struct {
    ulp_riscv_wakeup_source_t wakeup_source; /*!< ULP wakeup source */
} ulp_riscv_cfg_t;

#define ULP_RISCV_DEFAULT_CONFIG()                      \
    {                                                   \
        .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_TIMER, \
    }

/**
 * @brief Configure the ULP and run the program loaded into RTC memory
 *
 * @param cfg pointer to the config struct
 * @return  ESP_OK on success
 */
esp_err_t ulp_riscv_config_and_run(ulp_riscv_cfg_t* cfg);

/**
 * @brief Configure the ULP with default settings
 *        and run the program loaded into RTC memory
 *
 * @return  ESP_OK on success
 */
esp_err_t ulp_riscv_run(void);

/**
 * @brief Load ULP-RISC-V program binary into RTC memory
 *
 * Different than ULP FSM, the binary program has no special format, it is the ELF
 * file generated by RISC-V toolchain converted to binary format using objcopy.
 *
 * Linker script in components/ulp/ld/ulp_riscv.ld produces ELF files which
 * correspond to this format. This linker script produces binaries with load_addr == 0.
 *
 * @param program_binary pointer to program binary
 * @param program_size_bytes size of the program binary
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_SIZE if program_size_bytes is more than 8KiB
 */
esp_err_t ulp_riscv_load_binary(const uint8_t* program_binary, size_t program_size_bytes);

/**
 * @brief Stop the ULP timer
 *
 * @note This will stop the ULP from waking up if halted, but will not abort any program
 *       currently executing on the ULP.
 */
void ulp_riscv_timer_stop(void);


/**
 * @brief Resumes the ULP timer
 *
 * @note This will resume an already configured timer, but does no other configuration
 *
 */
void ulp_riscv_timer_resume(void);


/**
 * @brief Halts the program currently running on the ULP-RISC-V
 *
 * @note  Program will restart at the next ULP timer trigger if timer is still running.
 *        If you want to stop the ULP from waking up then call ulp_riscv_timer_stop() first.
 */
void ulp_riscv_halt(void);

#ifdef __cplusplus
}
#endif