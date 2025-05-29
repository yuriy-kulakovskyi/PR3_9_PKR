#include <gtest/gtest.h>
#include "../functions/functions.h"

std::string captureOutput(void (*func)(Node*), Node* root) {
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
  func(root);
  std::cout.rdbuf(old);
  return buffer.str();
}

TEST(FindFirstMinTest, EmptyTree) {
  Node* root = nullptr;
  std::string output = captureOutput(FindFirstMin, root);
  EXPECT_EQ(output, "Бінарне дерево порожнє\n");
}