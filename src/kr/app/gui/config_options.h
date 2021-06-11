#pragma once

enum GenLanguageType {
  LUA = 1,
  JSON = 2,
  CSHARP = 3,
};

struct ConfigOptions {
  ConfigOptions()
	  : gen_server_path{}, gen_client_path{}, gen_local_path{}, csv_tmp_path{},
        gen_server_type(LUA), gen_client_type(CSHARP), gen_local_type(JSON),
        log_level(1) {}

  QString data_path;
  QString gen_server_path;
  int gen_server_type;
  QString gen_client_path;
  int gen_client_type;
  QString gen_local_path;
  int gen_local_type;
  QString name_filters;
  int log_level;
  QString csv_tmp_path;
};