﻿/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)

@brief Inventory functions.

These are used to Manipulate Player or Vehicle Inventories.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "client/client.hpp"
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {

        struct rv_magazine_ammo {
            std::string name;
            int count;
            bool loaded;
            int type;
            std::string location;

            operator game_value() const {
                return game_value({name,
                                   static_cast<float>(count),
                                   loaded,
                                   static_cast<float>(type),
                                   location});
            }
        };

        struct rv_turret_magazine {
            std::string name;
            std::vector<int> turret_path;
            int count;
            int id;
            object creator;  // player
        };
        struct rv_container {
            std::string type;
            object container;
        };
        struct rv_weapon_accessories {
            std::string silencer;
            std::string flashlight_laserpointer;
            std::string optics;
            std::string bipod;
        };

        struct rv_weapon_state {
            std::string weapon;
            std::string muzzle;
            std::string mode;
            std::string magazine;
            float ammo_count;

            rv_weapon_state(game_value ret_game_value_) : weapon(ret_game_value_[0]),
                                                          muzzle(ret_game_value_[1]),
                                                          mode(ret_game_value_[2]),
                                                          magazine(ret_game_value_[3]),
                                                          ammo_count(ret_game_value_[4]) {}
        };

        /* potential namespace: items, inventory, campaign */
        void add_item_pool(sqf_string_const_ref item_name_, int item_count_);
        void add_magazine_pool(sqf_string_const_ref mag_name_, int mag_count_);
        void add_backpack_cargo(const object &vehicle_, sqf_string_const_ref packClassName_, int count_);
        void add_backpack_cargo_global(const object &vehicle_, sqf_string_const_ref packClassName_, int count_);
        void add_item_cargo(const object &object_, sqf_string_const_ref item_, int count_);
        void add_item_cargo_global(const object &object_, sqf_string_const_ref item_, int count_);
        void add_magazine(const object &obj_, sqf_string_const_ref classname_, int count_);
        void add_magazine_ammo_cargo(const object &obj_, sqf_string_const_ref classname_, int quantity_, int ammocount_);
        void add_magazine_cargo(const object &obj_, sqf_string_const_ref classname_, int count_);
        void add_magazine_cargo_global(const object &obj_, sqf_string_const_ref classname_, int count_);
        void add_magazines(const object &obj_, sqf_string_const_ref classname_, int count_);
        void add_magazine_turret(const object &obj_, sqf_string_const_ref classname_, const std::vector<int> &turretpath_, int ammocount_);
        void add_weapon_turret(const object &obj_, sqf_string_const_ref classname_, const std::vector<int> &turretpath_);
        void add_weapon_cargo(const object &obj_, sqf_string_const_ref classname_, int count_);
        void add_weapon_cargo_global(const object &obj_, sqf_string_const_ref classname_, int count_);
        void add_weapon_item(const object &obj_, sqf_string_const_ref weapon_name_, sqf_string_const_ref item_name_);
        void add_weapon_item(const object &obj_, sqf_string_const_ref weapon_name_, sqf_string_const_ref item_name_, int ammo_count_);
        void add_weapon_item(const object &obj_, sqf_string_const_ref weapon_name_, sqf_string_const_ref item_name_, int ammo_count_, sqf_string_const_ref muzzle_name_);
        sqf_return_string_list magazine_cargo(const object &obj_);
        sqf_return_string_list magazines(const object &obj_);
        std::vector<rv_turret_magazine> magazines_all_turrets(const object &obj_);
        std::vector<rv_magazine_ammo> magazines_ammo(const object &obj_);
        std::vector<rv_magazine_ammo> magazines_ammo_cargo(const object &obj_);
        std::vector<rv_magazine_ammo> magazines_ammo_full(const object &obj_);
        sqf_return_string_list magazines_detail(const object &obj_);
        sqf_return_string_list magazines_detail_backpack(const object &obj_);
        sqf_return_string_list magazines_detail_uniform(const object &obj_);
        sqf_return_string_list magazines_detail_vest(const object &obj_);

        sqf_return_string_list backpack_cargo(const object &box_);
        sqf_return_string_list backpack_items(const object &unit_);
        sqf_return_string_list backpack_magazines(const object &unit_);
        bool can_add(const object &obj_, sqf_string_const_ref classname_);
        bool can_add(const object &obj_, sqf_string_const_ref classname_, int count_);
        bool can_add_item_to_backpack(const object &obj_, sqf_string_const_ref classname_);
        bool can_add_item_to_backpack(const object &obj_, sqf_string_const_ref classname_, int count_);
        bool can_add_item_to_uniform(const object &obj_, sqf_string_const_ref classname_);
        bool can_add_item_to_uniform(const object &obj_, sqf_string_const_ref classname_, int count_);
        bool can_add_item_to_vest(const object &obj_, sqf_string_const_ref classname_);
        bool can_add_item_to_vest(const object &obj_, sqf_string_const_ref classname_, int count_);
        /* potential namespace: magazine, items, inventory */
        sqf_return_string current_magazine_detail(const object &veh_);

        void clear_all_items_from_backpack(const object &unit_);
        void clear_backpack_cargo(const object &box_);
        void clear_backpack_cargo_global(const object &box_);
        void clear_item_cargo(const object &box_);
        void clear_item_cargo_global(const object &box_);
        void clear_magazine_cargo(const object &veh_);
        void clear_magazine_cargo_global(const object &veh_);
        void clear_weapon_cargo(const object &veh_);
        void clear_weapon_cargo_global(const object &veh_);

        sqf_return_string handgun_magazine(const object &value_);
        sqf_return_string handgun_weapon(const object &value_);

        void remove_all_containers(const object &value_);
        void remove_all_handgun_items(const object &value_);
        void remove_all_items(const object &value_);
        void remove_all_items_with_magazines(const object &value_);
        void remove_all_primary_weapon_items(const object &value_);
        void remove_all_weapons(const object &value_);
        void remove_backpack(const object &value_);
        void remove_backpack_global(const object &value_);
        void remove_goggles(const object &value_);
        void remove_headgear(const object &value_);
        void remove_uniform(const object &value_);
        void remove_vest(const object &value_);

        sqf_return_string uniform(const object &value_);
        object uniform_container(const object &value_);
        object unit_backpack(const object &value_);
        sqf_return_string vest(const object &value_);
        object vest_container(const object &value_);
        sqf_return_string backpack(const object &unit_);
        object backpack_container(const object &unit_);
        object first_backpack(const object &value_);

        void add_backpack(const object &value0_, sqf_string_const_ref value1_);
        void add_backpack_global(const object &value0_, sqf_string_const_ref value1_);
        void add_goggles(const object &value0_, sqf_string_const_ref value1_);
        void add_handgun_item(const object &value0_, sqf_string_const_ref value1_);
        void add_headgear(const object &value0_, sqf_string_const_ref value1_);
        void add_item(const object &value0_, sqf_string_const_ref value1_);
        void add_item_to_backpack(const object &value0_, sqf_string_const_ref value1_);
        void add_item_to_uniform(const object &value0_, sqf_string_const_ref value1_);
        void add_item_to_vest(const object &value0_, sqf_string_const_ref value1_);
        void add_magazine(const object &value0_, sqf_string_const_ref value1_);
        void add_magazine_global(const object &value0_, sqf_string_const_ref value1_);
        void add_primary_weapon_item(const object &value0_, sqf_string_const_ref value1_);
        void add_secondary_weapon_item(const object &value0_, sqf_string_const_ref value1_);
        void add_uniform(const object &value0_, sqf_string_const_ref value1_);
        void add_vest(const object &value0_, sqf_string_const_ref value1_);
        void add_weapon(const object &value0_, sqf_string_const_ref value1_);
        void add_weapon_global(const object &value0_, sqf_string_const_ref value1_);

        void assign_item(const object &value0_, sqf_string_const_ref value1_);
        bool has_weapon(const object &value0_, sqf_string_const_ref value1_);
        void link_item(const object &value0_, sqf_string_const_ref value1_);
        bool is_uniform_allowed(const object &value0_, sqf_string_const_ref value1_);

        void remove_handgun_item(const object &value0_, sqf_string_const_ref value1_);
        void remove_item(const object &value0_, sqf_string_const_ref value1_);
        void remove_item_from_backpack(const object &value0_, sqf_string_const_ref value1_);
        void remove_item_from_uniform(const object &value0_, sqf_string_const_ref value1_);
        void remove_item_from_vest(const object &value0_, sqf_string_const_ref value1_);
        void remove_items(const object &value0_, sqf_string_const_ref value1_);
        void remove_magazine_global(const object &value0_, sqf_string_const_ref value1_);
        void remove_magazines(const object &value0_, sqf_string_const_ref value1_);

        void remove_primary_weapon_item(const object &value0_, sqf_string_const_ref value1_);
        void remove_secondary_weapon_item(const object &value0_, sqf_string_const_ref value1_);
        void remove_weapon(const object &value0_, sqf_string_const_ref value1_);
        void remove_weapon_global(const object &value0_, sqf_string_const_ref value1_);
        void select_weapon(const object &value0_, sqf_string_const_ref value1_);
        void unassign_item(const object &value0_, sqf_string_const_ref value1_);
        void unlink_item(const object &value0_, sqf_string_const_ref value1_);
        sqf_return_string_list items(const object &unit_);

        struct rv_throwable {
            std::string magazine_class_name;
            std::string muzzle_class_name;
            std::vector<float> ids;
        };

        rv_throwable current_throwable(const object &unit_);

        std::vector<object> every_backpack(const object &container_);

        std::vector<rv_container> every_container(const object &container_);

        struct rv_cargo {
            sqf_return_string_list types;
            std::vector<float> amounts;
        };

        std::vector<rv_cargo> get_backpack_cargo(const object &container_);
        std::vector<rv_cargo> get_item_cargo(const object &container_);
        std::vector<rv_cargo> get_magazine_cargo(const object &container_);
        std::vector<rv_cargo> get_weapon_cargo(const object &container_);
        sqf_return_string_list item_cargo(const object &container_);
        sqf_return_string_list weapon_cargo(const object &container_);
        sqf_return_string_list weapons(const object &unit_);
        sqf_return_string_list items_with_magazines(const object &unit_);
        sqf_return_string_list primary_weapon_items(const object &unit_);
        sqf_return_string_list primary_weapon_magazine(const object &unit_);
        sqf_return_string_list secondary_weapon_items(const object &unit_);
        sqf_return_string_list secondary_weapon_magazine(const object &unit_);

        struct rv_magazine {
            std::string name;
            int ammo;

            rv_magazine(const game_value &ret_game_value_) : name(ret_game_value_[0]),
                                                             ammo(ret_game_value_[1]) {}
        };

        struct rv_weapon_items {
            std::string weapon;
            std::string muzzle;
            std::string laser;
            std::string optics;
            rv_magazine magazine;
            std::optional<rv_magazine> grenade_launcher_magazine;
            std::string bipod;

            rv_weapon_items(const game_value &ret_game_value_) : weapon(ret_game_value_[0]),
                                                                 muzzle(ret_game_value_[1]),
                                                                 laser(ret_game_value_[2]),
                                                                 optics(ret_game_value_[3]),
                                                                 magazine(ret_game_value_[4]),
                                                                 grenade_launcher_magazine(ret_game_value_.size() > 6 ? ret_game_value_[5] : std::optional<rv_magazine>()),
                                                                 bipod(ret_game_value_.size() > 6 ? ret_game_value_[6] : ret_game_value_[5]) {}
        };

        std::vector<rv_weapon_items> weapons_items(const object &obj_);
        std::vector<rv_weapon_items> weapons_items_cargo(const object &veh_);
        struct rv_handgun_items {
            std::string silencer;
            std::string laser;
            std::string optics;
            std::string bipod;  //???

            explicit rv_handgun_items(const game_value &ret_game_value_) : silencer(ret_game_value_[0]),
                                                                           laser(ret_game_value_[1]),
                                                                           optics(ret_game_value_[2]),
                                                                           bipod(ret_game_value_[3]) {}

            explicit operator game_value() const {
                return game_value({silencer,
                                   laser,
                                   optics,
                                   bipod});
            }
        };

        rv_handgun_items handgun_items(const object &unit_);
        sqf_return_string_list soldier_magazines(const object &unit_);
        sqf_return_string_list vest_magazines(const object &unit_);
        sqf_return_string_list vest_items(const object &unit_);
        sqf_return_string_list uniform_magazines(const object &unit_);
        sqf_return_string_list uniform_items(const object &unit_);

        void remove_all_assigned_items(const object &value_);
        sqf_return_string_list assigned_items(const object &unit_);
        sqf_return_string current_magazine(const object &veh_);
        sqf_return_string current_muzzle(const object &gunner_);
        sqf_return_string current_weapon(const object &veh_);
        sqf_return_string current_weapon_mode(const object &gunner_);

        void load_magazine(const object &obj_, const std::vector<int> &turret_path_, sqf_string_const_ref weapon_name_, sqf_string_const_ref magazine_name_);

        struct rv_unit_description {
            std::string unit;
            std::string uniform;
            std::string vest;
            std::string backpack;

            rv_unit_description(const game_value &r_game_val)
                : unit(r_game_val[0]),
                  uniform(r_game_val[1]),
                  vest(r_game_val[2]),
                  backpack(r_game_val[3]) {}
        };

        rv_unit_description get_description(const object &unit_);

        float load(const object &value_);
        float load_abs(const object &value_);
        float load_backpack(const object &value_);
        float load_uniform(const object &value_);
        float load_vest(const object &value_);

        sqf_return_string secondary_weapon(const object &value_);
        sqf_return_string primary_weapon(const object &value_);

        void remove_magazine(const object &target_, sqf_string_const_ref magazine_);
        void remove_magazines_turret(const object &target_, sqf_string_const_ref magazine_, const std::vector<int> &turretPath_);
        void remove_magazine_turret(const object &target_, sqf_string_const_ref magazine_, const std::vector<int> &turretPath_);
        //Unimplemented in Engine - Arguments are nonsense
        void remove_weapon_attachment_cargo(const object &target_, const std::vector<game_value> &arg);
        //Unimplemented in Engine - Arguments are nonsense
        void remove_weapon_cargo(const object &target_, const std::vector<game_value> &arg);
        void remove_weapon_turret(const object &target_, sqf_string_const_ref weapon_name_, const std::vector<int> &turretPath_);
        void set_ammo(const object &target_, sqf_string_const_ref weapon_, int count);

        struct rv_magazine_info {
            std::string magazine;
            int ammo;
            int count;

            rv_magazine_info(const game_value &ret_game_value_) : magazine(ret_game_value_[0]),
                                                                  ammo(ret_game_value_.size() > 2 ? static_cast<int>(ret_game_value_[1]) : -1),
                                                                  count(ret_game_value_.size() > 2 ? ret_game_value_[2] : ret_game_value_[1]) {}

            operator game_value() const {
                if (ammo != -1)
                    return game_value({magazine,
                                       static_cast<float>(ammo),
                                       static_cast<float>(count)});
                return game_value({magazine,
                                   static_cast<float>(count)});
            }
        };

        struct rv_weapon_info {
            std::string weapon;
            std::string silencer = "";
            std::string laser;
            std::string optics;
            rv_magazine_info primary_muzzle_magazine;
            rv_magazine_info secondary_muzzle_magazine;
            std::string bipod;

            rv_weapon_info(const game_value &ret_game_value_) : weapon(ret_game_value_[0]),
                                                                silencer(ret_game_value_[1]),
                                                                laser(ret_game_value_[2]),
                                                                optics(ret_game_value_[3]),
                                                                primary_muzzle_magazine(ret_game_value_[4]),
                                                                secondary_muzzle_magazine({ret_game_value_[5]}),
                                                                bipod(ret_game_value_[6]) {}

            explicit operator game_value() const {
                return game_value({weapon,
                                   silencer,
                                   laser,
                                   optics,
                                   primary_muzzle_magazine,
                                   secondary_muzzle_magazine,
                                   bipod});
            }
        };

        struct rv_container_info {
            std::string container;
            std::vector<rv_magazine_info> items;

            rv_container_info(const game_value &ret_game_value_) : container(ret_game_value_[0]) {
                auto &arr = ret_game_value_[1].to_array();
                for (auto &it : arr)
                    items.push_back(it);
            }

            explicit operator game_value() const {
                return game_value({container,
                                   auto_array<game_value>(items.begin(), items.end())});
            }
        };

        struct rv_unit_loadout {
            rv_weapon_info primary;
            rv_weapon_info secondary;
            rv_weapon_info handgun;
            rv_container_info uniform;
            rv_container_info vest;
            rv_container_info backpack;
            std::string headgear;
            std::string facewear;
            rv_weapon_info binocular;
            std::vector<std::string> assigned_items;

            rv_unit_loadout(const game_value &ret_game_value_) : primary(ret_game_value_[0]),
                                                                 secondary({ret_game_value_[1]}),
                                                                 handgun(ret_game_value_[2]),
                                                                 uniform(ret_game_value_[3]),
                                                                 vest(ret_game_value_[4]),
                                                                 backpack(ret_game_value_[5]),
                                                                 headgear(ret_game_value_[6]),
                                                                 facewear(ret_game_value_[7]),
                                                                 binocular({ret_game_value_[8]}),
                                                                 assigned_items({ret_game_value_[9]}) {}

            explicit operator game_value() const {
                return game_value({static_cast<game_value>(primary),
                                   static_cast<game_value>(secondary),
                                   static_cast<game_value>(handgun),
                                   static_cast<game_value>(uniform),
                                   static_cast<game_value>(vest),
                                   static_cast<game_value>(backpack),
                                   headgear,
                                   facewear,
                                   static_cast<game_value>(binocular),
                                   auto_array<game_value>(assigned_items.begin(), assigned_items.end())});
            }
        };

        rv_unit_loadout get_unit_loadout(const object &obj_);
        rv_unit_loadout get_unit_loadout(const config &cfg_);
        void set_unit_loadout(const object &obj_, const rv_unit_loadout &loadout_, bool rearm_ = false);

        //inventory
        rv_weapon_accessories weapon_accessories(const object &unit_, sqf_string_const_ref weapon_class_);
        rv_weapon_accessories weapon_accessories_cargo(const object &container_, int weapon_id_, int creator_id_);
        sqf_return_string_list magazines_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        int magazine_turret_ammo(sqf_string_const_ref magazine_class_, const std::vector<int> &turret_path_);
        void set_magazine_turret_ammo(const object &vehicle_, sqf_string_const_ref magazine_class_, int ammo_count_, const std::vector<int> &turret_path_);
        void set_vehicle_ammo(const object &value0_, float value1_);
        void set_vehicle_ammo_def(const object &value0_, float value1_);

        void set_fuel_cargo(const object &value0_, float value1_);
        void set_repair_cargo(const object &value0_, float value1_);
        void pick_weapon_pool(const object &value_);
        void put_weapon_pool(const object &value_);
        float query_items_pool(sqf_string_const_ref value_);
        float query_magazine_pool(sqf_string_const_ref value_);
        float query_weapon_pool(sqf_string_const_ref value_);
        float ammo(const object &value0_, sqf_string_const_ref value1_);
        void force_add_uniform(const object &value0_, sqf_string_const_ref value1_);
        void set_ammo_cargo(const object &value0_, float value1_);
        void add_weapon_pool(sqf_string_const_ref weapon_name_, int count_);
        sqf_return_string current_magazine_detail_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        sqf_return_string current_magazine_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        sqf_return_string current_weapon_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        sqf_return_string_list get_artillery_ammo(const std::vector<object> &units_);

        void clear_item_pool();
        void clear_magazine_pool();
        void clear_weapon_pool();

        sqf_return_string binocular(const object &unit_);

        float gear_idcammo_count(float value_);

        float get_ammo_cargo(const object &value_);

        float get_fuel_cargo(const object &value_);
        float get_repair_cargo(const object &value_);
        sqf_return_string goggles(const object &value_);
        sqf_return_string headgear(const object &value_);
        sqf_return_string hmd(const object &value_);

        rv_weapon_state weapon_state(const object &unit_);
        rv_weapon_state weapon_state(const object &vehicle_, const std::vector<int> &turret_path_, std::optional<sqf_return_string> weapon_ = std::optional<sqf_return_string>());

    }  // namespace sqf
}  // namespace intercept
