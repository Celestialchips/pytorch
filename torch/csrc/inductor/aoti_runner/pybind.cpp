#include <torch/csrc/inductor/aoti_runner/model_container_runner_cpu.h>
#ifdef USE_CUDA
#include <torch/csrc/inductor/aoti_runner/model_container_runner_cuda.h>
#endif

#include <torch/csrc/utils/pybind.h>

namespace torch::inductor {

void initAOTIRunnerBindings(PyObject* module) {
  auto rootModule = py::handle(module).cast<py::module>();
  auto m = rootModule.def_submodule("_aoti");

  py::class_<AOTIModelContainerRunnerCpu>(m, "AOTIModelContainerRunnerCpu")
      .def(py::init<const std::string&, int>())
      .def("run", &AOTIModelContainerRunnerCpu::run)
      .def("get_call_spec", &AOTIModelContainerRunnerCpu::get_call_spec);

#ifdef USE_CUDA
  py::class_<AOTIModelContainerRunnerCuda>(m, "AOTIModelContainerRunnerCuda")
      .def(py::init<const std::string&, int>())
      .def("run", &AOTIModelContainerRunnerCuda::run)
      .def("get_call_spec", &AOTIModelContainerRunnerCuda::get_call_spec);
#endif
}
} // namespace torch::inductor
