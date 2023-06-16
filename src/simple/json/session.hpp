/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <fmt/format.h>

#include <memory>
#include <string>

#include "roq/io/net/tcp/connection.hpp"

#include "roq/web/rest/server.hpp"

#include "simple/shared.hpp"

#include "simple/json/response.hpp"

namespace simple {
namespace json {

// note! supports both rest and websocket

struct Session final : public roq::web::rest::Server::Handler {
  Session(uint64_t session_id, roq::io::net::tcp::Connection::Factory &, Shared &);

 protected:
  // web::rest::Server::Handler
  void operator()(roq::web::rest::Server::Disconnected const &) override;
  void operator()(roq::web::rest::Server::Request const &) override;
  void operator()(roq::web::rest::Server::Text const &) override;
  void operator()(roq::web::rest::Server::Binary const &) override;

  // routes

  void get_exchanges(Response &, roq::web::rest::Server::Request const &);
  void get_symbols(Response &, roq::web::rest::Server::Request const &);

  void post_order(Response &, roq::web::rest::Server::Request const &);
  void delete_order(Response &, roq::web::rest::Server::Request const &);

 private:
  uint64_t const session_id_;
  std::unique_ptr<roq::web::rest::Server> server_;
  Shared &shared_;
};

}  // namespace json
}  // namespace simple
