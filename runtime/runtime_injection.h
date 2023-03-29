// Compiler for PHP (aka KPHP)
// Copyright (c) 2023 LLC «V Kontakte»
// Distributed under the GPL v3 License, see LICENSE.notice.txt

#pragma once

#include <functional>

#include "runtime/kphp_core.h"

struct C$KphpJobWorkerRequest;

namespace runtime_injection {

using on_fork_start_callback_t = std::function<void(int64_t parent_fork_id, int64_t started_fork_id)>;
using on_fork_finish_callback_t = std::function<void(int64_t fork_id)>;
using on_fork_switch_callback_t = std::function<void(int64_t old_fork_id, int64_t new_fork_id)>;

using on_rpc_request_start_callback_t = std::function<
  void(int64_t rpc_query_id, int64_t actor_port, int64_t tl_magic, int64_t bytes_sent, double start_timestamp, bool is_no_result)
>;
using on_rpc_request_finish_callback_t = std::function<
  void(int64_t rpc_query_id, int64_t bytes_recv_or_error_code, double duration_sec, int64_t awaiting_fork_id)
>;

using on_job_request_start_callback_t = std::function<
  void(int64_t job_id, const class_instance<C$KphpJobWorkerRequest> &job, double start_timestamp, bool is_no_reply)
>;
using on_job_request_finish_callback_t = std::function<
  void(int64_t job_id, const Optional<int64_t> &error_code, double duration_sec, int64_t awaiting_fork_id)
>;

using on_net_to_script_switch_callback_t = std::function<void(double now_timestamp, double net_time_delta)>;

using on_shutdown_functions_start_callback_t = std::function<void(int64_t shutdown_functions_cnt, int64_t shutdown_type, double now_timestamp)>;
using on_shutdown_functions_finish_callback_t = std::function<void(double now_timestamp)>;

using on_tracing_vslice_start_callback_t = std::function<void(int64_t vslice_id, double start_timestamp)>;
using on_tracing_vslice_finish_callback_t = std::function<void(int64_t vslice_id, double end_timestamp, int64_t memory_used)>;

extern on_fork_start_callback_t on_fork_start;
extern on_fork_finish_callback_t on_fork_finish;
extern on_fork_switch_callback_t on_fork_switch;
extern on_rpc_request_start_callback_t on_rpc_request_start;
extern on_rpc_request_finish_callback_t on_rpc_request_finish;
extern on_job_request_start_callback_t on_job_request_start;
extern on_job_request_finish_callback_t on_job_request_finish;
extern on_net_to_script_switch_callback_t on_net_to_script_ctx_switch;
extern on_shutdown_functions_start_callback_t on_shutdown_functions_start;
extern on_shutdown_functions_finish_callback_t on_shutdown_functions_finish;
extern on_tracing_vslice_start_callback_t on_tracing_vslice_start;
extern on_tracing_vslice_finish_callback_t on_tracing_vslice_finish;

template<typename F, typename ...Args>
void invoke_callback(F &f, Args &&... args) noexcept {
  if (f) {
    f(std::forward<Args>(args)...);
  }
}

void free_callbacks();

} // namespace runtime_injection


// TODO: ensure this callbacks never swap context
void f$register_kphp_on_fork_callbacks(const runtime_injection::on_fork_start_callback_t &on_fork_start,
                                       const runtime_injection::on_fork_finish_callback_t &on_fork_finish,
                                       const runtime_injection::on_fork_switch_callback_t &on_fork_switch);
void f$register_kphp_on_rpc_query_callbacks(const runtime_injection::on_rpc_request_start_callback_t &on_start,
                                            const runtime_injection::on_rpc_request_finish_callback_t &on_finish);
void f$register_kphp_on_job_worker_callbacks(const runtime_injection::on_job_request_start_callback_t &on_start,
                                             const runtime_injection::on_job_request_finish_callback_t &on_finish);
void f$register_kphp_on_swapcontext_callbacks(const runtime_injection::on_net_to_script_switch_callback_t &on_net_to_script_switch);
void f$register_kphp_on_shutdown_callbacks(const runtime_injection::on_shutdown_functions_start_callback_t &on_start,
                                           const runtime_injection::on_shutdown_functions_finish_callback_t &on_finish);
void f$register_kphp_on_tracing_vslice_callbacks(const runtime_injection::on_tracing_vslice_start_callback_t &on_start,
                                                 const runtime_injection::on_tracing_vslice_finish_callback_t &on_finish);
