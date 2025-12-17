#include <iostream> // std::cout
#include <memory_resource> // std::pmr
#include <format> // std::format
#include <stacktrace> // std::stacktrace
#include <bitset> // std::bitset

#include <CrystalSpatial/spatial.h> // crystal::spatial::Space

int main() {
  class NullResource : public std::pmr::memory_resource {
    void* do_allocate(size_t size, size_t align) override {
      std::cout << std::format(
        "[Invalid Deallocation]\tsize: {:x}\talign: {:x}",
        size,
        align
      ) << std::endl;
      std::cout << std::stacktrace::current() << std::endl;
      return std::pmr::null_memory_resource()->allocate(size, align);
    }
    void do_deallocate(void* ptr, size_t size, size_t align) override {
      std::cout << std::format(
        "[Invalid Deallocation]\tptr: {:x}\tsize: {:x}\talign: {:x}",
        (long long)ptr,
        size,
        align
      ) << std::endl;
      std::cout << std::stacktrace::current() << std::endl;
      return std::pmr::null_memory_resource()->deallocate(ptr, size, align);
    }
    bool do_is_equal(const memory_resource& other) const noexcept override {
      std::cout << std::format("[Invalid Isequal]") << std::endl;
      std::cout << std::stacktrace::current() << std::endl;
      return std::pmr::null_memory_resource()->is_equal(other);
    };
  };
  std::cout << std::hex;
  NullResource null_resource;
  std::pmr::set_default_resource(&null_resource);
  crystal::spatial::Space space{};
  auto ss1 = space.CreateSubSpace();
  std::cout << "ss1:\t" << std::bitset<64>(ss1.get()).to_ullong() << std::endl;

  auto vec1 = space.CreateVec();
  std::cout << "vec1:\t" << std::bitset<64>(vec1.get()).to_ullong() << std::endl;

  auto ss2 = space.CreateSubSpace(ss1);
  std::cout << "ss2:\t" << std::bitset<64>(ss2.get()).to_ullong() << std::endl;

  auto vec2 = space.CreateVec(ss1);
  std::cout << "vec2:\t" << std::bitset<64>(vec2.get()).to_ullong() << std::endl;
  return 0;
}
