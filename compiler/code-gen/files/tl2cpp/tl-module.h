#pragma once

#include "compiler/code-gen/files/tl2cpp/tl2cpp-utils.h"
#include "compiler/code-gen/includes.h"

namespace tl2cpp {
class Module;

extern std::unordered_map<std::string, Module> modules;

extern std::set<std::string> modules_with_functions;

// Модуль - это два .cpp/.h файла, соответстсвующие одному модулю tl-схемы
class Module {
public:
  std::vector<vk::tl::type *> target_types;
  std::vector<vk::tl::combinator *> target_functions;
  IncludesCollector h_includes;
  IncludesCollector cpp_includes;
  std::string name;

  Module() = default;

  explicit Module(string name) :
    name(std::move(name)) {}

  void compile(CodeGenerator &W) const {
    compile_tl_h_file(W);
    if (!is_empty()) {
      compile_tl_cpp_file(W);
    }
  }

  void compile_tl_h_file(CodeGenerator &W) const;

  void compile_tl_cpp_file(CodeGenerator &W) const;

  void add_obj(const std::unique_ptr<vk::tl::combinator> &f);

  void add_obj(const std::unique_ptr<vk::tl::type> &t);

  static std::string get_module_name(const std::string &type_or_comb_name) {
    auto pos = type_or_comb_name.find('.');
    return pos == std::string::npos ? "common" : type_or_comb_name.substr(0, pos);
  }

  static void add_to_module(const std::unique_ptr<vk::tl::type> &t) {
    ensure_existence(get_module_name(t->name)).add_obj(t);
  }

  static void add_to_module(const std::unique_ptr<vk::tl::combinator> &c) {
    ensure_existence(get_module_name(c->name)).add_obj(c);
  }

  bool is_empty() const;

private:
  static Module &ensure_existence(const std::string &module_name) {
    if (modules.find(module_name) == modules.end()) {
      modules[module_name] = Module(module_name);
    }
    return modules[module_name];
  }

  void update_dependencies(const std::unique_ptr<vk::tl::combinator> &combinator);

  void update_dependencies(const std::unique_ptr<vk::tl::type> &t);

  void collect_deps_from_type_tree(vk::tl::expr_base *expr);
};

}
