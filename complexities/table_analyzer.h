#pragma once

#include <complexities//complexity_analyzer.h>

namespace ds::utils {
    template<typename TabType>
    class TabAnalyzer : public ComplexityAnalyzer<TabType> {
    protected:
        explicit ListAnalyzer(const std::string& name);
    protected:
        void growToSize(TabType& structure, size_t size) override;
};
    template<typename TabType>
    class SortedTabInsertAnalyzer : public TabAnalyzer<TabType>{
    protected:
        explicit ListAnalyzer(const std::string& name);
    protected:
        void executeOperation(TabType& structure) override;
    };
    template<typename TabType>
class SortedTabRemoveAnalyzer : public TabAnalyzer<TabType>
        protected:
            explicit ListAnalyzer(const std::string& name);
        protected:
            void executeOperation(TabType& structure) override;
};


// ----
class BVSTabAnalyzer : public ComplexityAnalyzer<BVS<int, int>> {
protected:
explicit ListAnalyzer(const std::string& name);
protected:
void growToSize(SortedSequenceTable<int, int>& structure, size_t size) override;
};
class BVSTabInsertAnalyzer : public SortedTabAnalyzer {
protected:
    explicit ListAnalyzer(const std::string& name);
protected:
    void executeOperation(BVS<int, int>& structure) override;
};
class BVSTabRemoveAnalyzer : public SortedTabAnalyzer {
protected:
    explicit ListAnalyzer(const std::string& name);
protected:
    void executeOperation(BVS<int, int>& structure) override;
};
}