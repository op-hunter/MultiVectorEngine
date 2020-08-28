#include <unordered_map>
#include "MilvusApi.h"
#include "Status.h"
#include "BaseEngine.h"
#include "MultiVectorCollection.h"


namespace milvus {
namespace multivector {

class MultiVectorEngine : BaseEngine {
 public:
    MultiVectorEngine() {}
    MultiVectorEngine(const std::string &ip, const std::string &port) {}

    Status
    CreateCollection(const std::string &collection_name, milvus::MetricType metric_type,
                     const std::vector<int64_t> &dimensions,
                     const std::vector<int64_t> &index_file_sizes) override;

    // todo: 1 find collection_name in collections_
    // todo: 2 for id in collections_[collection_name].second:
    //  do milvus.dropindex(GenerateChildCollectionName(collection_name, id));
    Status
    DropCollection(const std::string &collection_name) override;

    Status
    Insert(const std::string &collection_name,
           const std::vector<RowEntity> &entity_arrays,
           std::vector<int64_t> &id_arrays) override;

    Status
    Delete(const std::string &collection_name, const std::vector<int64_t> &id_arrays) override;

    Status
    CreateIndex(const std::string &collection_name, milvus::IndexType index_type, const std::string &param) override;

    Status
    DropIndex(const std::string &collection_name) override;

    Status
    Search(const std::string &collection_name, const std::vector<float> &weight,
           const std::vector<std::vector<milvus::Entity>> &entity_array,
           int64_t topk, milvus::TopKQueryResult &topk_query_results) override;

 private:
    // maintain collection list for all collections
    // collections.first is the user provided collection name
    // collections.second is the child collection(s) list
    std::unordered_map<std::string, MultiVectorCollectionPtr> collections_;
};

} // namespace multivector
} // namespace milvus
