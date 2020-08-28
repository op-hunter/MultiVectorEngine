#include "MilvusApi.h"
#include "Status.h"
#include "BaseEngine.h"


namespace milvus {
namespace multivector {

class MultiVectorCollection {
 public:
    MultiVectorCollection() = delete;
    MultiVectorCollection(const std::shared_ptr<milvus::Connection> server_conn, const std::string collection_name, const milvus::MetricType metric_type) : collection_name_(collection_name), metric_type_(metric_type), conn_ptr_(server_conn) {}

    virtual Status
    CreateCollection(std::vector<int64_t> dimensions,
                     std::vector<int64_t> index_file_sizes) = 0;

    virtual Status
    DropCollection() = 0;

    virtual Status
    Insert(const std::vector<RowEntity> &entity_arrays,
           std::vector<int64_t> &id_arrays) = 0;

    virtual Status
    Delete(std::vector<int64_t> &id_arrays) = 0;

    virtual Status
    CreateIndex(std::string param) = 0;

    virtual Status
    DropIndex() = 0;

    virtual Status
    Search(std::vector<float> weight,
           const std::vector<std::vector<milvus::Entity>> &entity_array,
           int64_t topk, milvus::TopKQueryResult &topk_query_results) = 0;

 private:
    static std::string
    GenerateChildCollectionName(const std::string &collection_prefix, int64_t idx) {
        return collection_prefix + "_" + std::to_string(idx);
    }

 private:
    std::string collection_name_;
    milvus::MetricType metric_type_;
    std::vector<int64_t> child_collection_ids_;
    std::shared_ptr<milvus::Connection> conn_ptr_ = nullptr;
};

using MultiVectorCollectionPtr = std::shared_ptr<MultiVectorCollection>;

} // namespace multivector
} // namespace milvus
