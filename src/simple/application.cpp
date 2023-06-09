/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "simple/application.hpp"

#include <vector>

#include "roq/exceptions.hpp"

#include "roq/logging.hpp"

#include "roq/io/engine/context_factory.hpp"

#include "simple/config.hpp"
#include "simple/controller.hpp"
#include "simple/settings.hpp"

using namespace std::literals;

namespace simple {

// === IMPLEMENTATION ===

int Application::main(roq::args::Parser const &args) {
  auto params = args.params();
  auto settings = Settings::create(args);
  auto config = Config::parse_file(settings.config_file);
  roq::log::info("config={}"sv, config);
  auto context = roq::io::engine::ContextFactory::create_libevent();
  try {
    Controller{settings, config, *context, params}.run();
    return EXIT_SUCCESS;
  } catch (...) {
    try {
      throw;
    } catch (roq::Exception &e) {
      roq::log::error("Unhandled exception: {}"sv, e);
    } catch (std::exception &e) {
      roq::log::error(R"(Unhandled exception: type="{}", what="{}")"sv, typeid(e).name(), e.what());
    } catch (...) {
      auto e = std::current_exception();
      roq::log::error(R"(Unhandled exception: type="{}")"sv, typeid(e).name());
    }
  }
  return EXIT_FAILURE;
}

}  // namespace simple
