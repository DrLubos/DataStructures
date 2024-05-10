#pragma once

#include <complexities//complexity_analyzer.h>
#include <libds/adt/table.h>
#include <libds/adt/list.h>
#include <complexities/list_analyzer.h>

namespace ds::utils {
    template<class TabType>
    class TabAnalyzer : public ComplexityAnalyzer<TabType> {
    protected:
        explicit TabAnalyzer(const std::string &name);

    protected:
        void growToSize(TabType &structure, size_t size) override;

        size_t getRandomIndex() const;

        int getRandomData() const;

    protected:
        std::default_random_engine rngData_;
        std::default_random_engine rngIndex_;
        size_t index_;
        int data_;
        ds::adt::ImplicitList<int> list;
    };

    template<class TabType>
    class TabInsertAnalyzer : public TabAnalyzer<TabType> {
    public:
        explicit TabInsertAnalyzer(const std::string &name);

    protected:
        void executeOperation(TabType &structure) override;
    };

    template<class TabType>
    class TabRemoveAnalyzer : public TabAnalyzer<TabType> {
    public:
        explicit TabRemoveAnalyzer(const std::string &name);

    protected:
        void executeOperation(TabType &structure) override;
    };

    class TabsAnalyzer : public CompositeAnalyzer
    {
        public:
        TabsAnalyzer();
    };

    template<class List>
    TabAnalyzer<List>::TabAnalyzer(const std::string& name) :
            ComplexityAnalyzer<List>(name),
            rngData_(144),
            rngIndex_(144),
            index_(0),
            data_(0)
    {
        ComplexityAnalyzer<List>::registerBeforeOperation([this](List& list)
                                                          {
                                                              std::uniform_int_distribution<size_t> indexDist(0, list.size() - 1);
                                                              index_ = indexDist(rngIndex_);
                                                              data_ = rngData_();
                                                          });
    }


    template<typename TabType>
    void TabAnalyzer<TabType>::growToSize(TabType& structure, size_t size) {
        const size_t toInsert = size - structure.size();
        int key = 0;
        int value = 0;
        for (size_t i = 0; i < toInsert; ++i)
        {
            key = rngData_();
            value = rngData_();
            //std::cout << "Key: " << key << " Value: " << value << "\n";
            structure.insert(key, value);
            list.insertLast(key);
        }
    }

    template<class List>
    size_t TabAnalyzer<List>::getRandomIndex() const
    {
        return index_;
    }

    template<class List>
    int TabAnalyzer<List>::getRandomData() const
    {
        return data_;
    }

    template <class List>
    TabInsertAnalyzer<List>::TabInsertAnalyzer(const std::string& name) :
            TabAnalyzer<List>(name)
    {
    }

    template <class List>
    void TabInsertAnalyzer<List>::executeOperation(List& structure)
    {
        auto data = this->getRandomData();
        structure.insert(this->rngData_(), data);
    }

    template <class List>
    TabRemoveAnalyzer<List>::TabRemoveAnalyzer(const std::string& name) :
            TabAnalyzer<List>(name)
    {
    }

    template <class List>
    void TabRemoveAnalyzer<List>::executeOperation(List& structure)
    {
        if (structure.isEmpty()) {
            return;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, this->list.size()- 1);
        int randomIndex = distrib(gen);
        std::cout << "List size: " << this->list.size() << "\nRand inde: " << randomIndex << std::endl;
        int valueFromList = this->list.access(randomIndex);
        if (structure.contains(valueFromList)) {
            structure.remove(valueFromList);
        }
        //structure.remove(valueFromList);
        this->list.remove(randomIndex);
    }

    //----------

    inline TabsAnalyzer::TabsAnalyzer() :
            CompositeAnalyzer("Tabs")
    {
        //this->addAnalyzer(std::make_unique<ListInsertAnalyzer<std::vector<int>>>("vector-insert"));
        //this->addAnalyzer(std::make_unique<TabInsertAnalyzer<ds::adt::SortedSTab<int, int>>>("tab-insert"));
        //this->addAnalyzer(std::make_unique<ListRemoveAnalyzer<std::vector<int>>>("vector-remove"));
        //this->addAnalyzer(std::make_unique<ds::adt::SortedSequenceTable<int, int>>>("tab-remove"));
        this->addAnalyzer(std::make_unique<TabInsertAnalyzer<ds::adt::SortedSTab<int, int>>>("tab-insert"));
        this->addAnalyzer(std::make_unique<TabRemoveAnalyzer<ds::adt::SortedSequenceTable<int, int>>>("tab-remove"));
    }

}




// Uprava
/*
namespace ds::utils {
    template<typename TabType>
    class TabAnalyzer : public ComplexityAnalyzer<TabType> {
    protected:
        explicit TabAnalyzer(const std::string& name);

    protected:
        void growToSize(TabType& structure, size_t size) override;
    };

    template<typename TabType>
    class SortedTabInsertAnalyzer : public TabAnalyzer<TabType> {
    protected:
        explicit SortedTabInsertAnalyzer(const std::string& name);

    protected:
        void executeOperation(TabType& structure) override;
    };

    template<typename TabType>
    class SortedTabRemoveAnalyzer : public TabAnalyzer<TabType> {
    protected:
        explicit SortedTabRemoveAnalyzer(const std::string& name);

    protected:
        void executeOperation(TabType& structure) override;
    };
}
 */





// Z hodiny
/*
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
}*/