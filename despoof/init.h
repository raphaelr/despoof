#pragma once

#include <memory>
#include "context.h"

bool despoof_init(int argc, char **argv, std::unique_ptr<despoof::context> &ctx);
void despoof_run(despoof::context &ctx);
