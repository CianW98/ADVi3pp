/**
 * ADVi3++ Firmware For Wanhao Duplicator i3 Plus (based on Marlin 2)
 *
 * Copyright (C) 2017-2021 Sebastien Andrivet [https://github.com/andrivet/]
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "../../lib/ADVstd/array.h"
#include "../core/screen.h"

namespace ADVi3pp {

//! PID Settings Page
struct Pid
{
    float Kp_, Ki_, Kd_;
    uint16_t temperature_;
};

struct PidSettings: Screen<PidSettings>
{
    PidSettings();

    void add_pid(TemperatureKind kind, uint16_t temperature);
    void choose_best_pid(TemperatureKind kind, uint16_t temperature);

private:
    static const size_t NB_PIDs = 3;

    bool do_dispatch(KeyValue key_value);
    Page do_prepare_page();
    void do_write(EepromWrite& eeprom) const;
    bool do_validate(EepromRead& eeprom);
    void do_read(EepromRead& eeprom);
    void do_reset();
    uint16_t do_size_of() const;
    void do_save_command();
    void do_back_command();
    void save_bed_pid() const;
    void hotend_command();
    void save_hotend_pid() const;
    void bed_command();
    void previous_command();
    void next_command();
    void set_marlin_pid() const;
    void get_marlin_pid();
    void to_lcd() const;
    void from_lcd();

    adv::array<Pid, PidSettings::NB_PIDs>& get_pids();
    const adv::array<Pid, PidSettings::NB_PIDs>& get_pids() const;
    Pid& get_pid();
    const Pid& get_pid() const;

private:
    adv::array<Pid, NB_PIDs> hotend_pid_{};
    adv::array<Pid, NB_PIDs> bed_pid_{};
    TemperatureKind kind_ = TemperatureKind::Hotend;
    uint8_t index_ = 0;

    friend Parent;
};

extern PidSettings pid_settings;

}
