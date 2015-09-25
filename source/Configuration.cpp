/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Configuration.hh"
#include "Debug.hh"


namespace boca {

Configuration::Configuration()
{
    ReadConfig("Standard");
}

Configuration::Configuration(std::string const& config_name)
{
    ReadConfig(config_name);
}

boca::Mass Configuration::Mass()
{
    try {
        return double(config().lookup("Mass")) * GeV;
    } catch (libconfig::SettingNotFoundException const& setting_not_found_exception) {
        Error("No 'Mass' setting in configuration file");
        throw;
    } catch (libconfig::SettingTypeException const& setting_type_exception) {
        Error("'Mass' setting has wrong type");
        throw;
    }
}

Momentum Configuration::PreCut()
{
    try {
        return double(config().lookup("PreCut")) * GeV;
    } catch (libconfig::SettingNotFoundException const& setting_not_found_exception) {
        Error("No 'PreCut' setting in configuration file");
        throw;
    } catch (libconfig::SettingTypeException const& setting_type_exception) {
        Error("'PreCut' setting has wrong type");
        throw;
    }
}

long Configuration::EventNumberMax()
{
    try {
        return config().lookup("EventNumberMax");
    } catch (libconfig::SettingNotFoundException const& setting_not_found_exception) {
        Error("No 'EventNumberMax' setting in configuration file");
        throw;
    } catch (libconfig::SettingTypeException const& setting_type_exception) {
        Error("'EventNumberMax' setting has wrong type");
        throw;
    }
}

int Configuration::BackgroundFileNumber()
{
    try {
        return config().lookup("BackgroundFileNumber");
    } catch (libconfig::SettingNotFoundException const& setting_not_found_exception) {
        Error("No 'BackgroundFileNumber' setting in configuration file");
        throw;
    } catch (libconfig::SettingTypeException const& setting_type_exception) {
        Error("'BackgroundFileNumber' setting has wrong type");
        throw;
    }
}

ColliderType Configuration::ColliderType()
{
    try {
        std::string Collider = config().lookup("ColliderType");
        if (Collider == "LHC") return boca::ColliderType::LHC;
        else if (Collider == "LE") return boca::ColliderType::LE;
        else if (Collider == "FHC") return boca::ColliderType::FHC;
    } catch (libconfig::SettingNotFoundException const& setting_not_found_exception) {
        Error("No 'ColliderType' setting in configuration file");
        throw;
    } catch (libconfig::SettingTypeException const& setting_type_exception) {
        Error("'ColliderType' setting has wrong type");
        throw;
    }
    return boca::ColliderType::LHC;
}

void Configuration::WriteConfig(std::string const& config_name)
{
    libconfig::Setting& root = config().getRoot();
    libconfig::Setting& mass = root.add("Mass",  libconfig::Setting::TypeInt) = 1000;
    libconfig::Setting& pre_cut = root.add("PreCut",  libconfig::Setting::TypeInt) = 1000;
    libconfig::Setting& event_number_max = root.add("EventNumberMax",  libconfig::Setting::TypeInt) = 10000;
    libconfig::Setting& background_file_number = root.add("BackgroundFileNumber",  libconfig::Setting::TypeInt) = 1;
    libconfig::Setting& collider_type = root.add("ColliderType",  libconfig::Setting::TypeString) = "LE";
    try {
        config().writeFile(ConfigFile(config_name).c_str());
        Error("New configuration successfully written to", ConfigFile(config_name));
    } catch (libconfig::FileIOException const& file_io_exception) {
        Error("I/O error while writing file", ConfigFile(config_name));
    }
}

void Configuration::ReadConfig(std::string const& config_name)
{
    try {
        config().readFile(ConfigFile(config_name).c_str());
    } catch (libconfig::FileIOException const& file_io_exception) {
        Error("I/O error while reading file");
        WriteConfig(config_name);
    } catch (const libconfig::ParseException& ParseException) {
        Error("Parse error at", ParseException.getFile(), ParseException.getLine(), ParseException.getError());
    }
}

std::string Configuration::ConfigFile(std::string const& config_name)
{
    return config_name + ".cfg";
}

}

