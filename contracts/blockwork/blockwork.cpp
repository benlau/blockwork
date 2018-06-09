#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class blockwork : public eosio::contract {

public:
    typedef enum {
        OPENED,
        COMPLETED,
        PAID
    } State;

    blockwork(account_name s) : contract(s), _job(s, s) {
    }

    /// @abi action
    void create(account_name submitter,
                uint64_t jobId,
                std::string jobName,
                std::string jobDescription) {
        require_auth(submitter);

        eosio_assert(_job.find(jobId) == _job.end(), "This jobId already exists in the addressbook");

        _job.emplace(get_self(), [&]( auto& j ) {
           j.jobId = jobId;
           j.submitter = submitter;
           j.jobName = jobName;
           j.jobDescription = jobDescription;
           j.state = OPENED;
           j.reviewer = 0;
        });
    }

private:
   /// @TODO timestamp
    /// @abi table job
    struct job {
        uint64_t jobId;
        account_name submitter;
        account_name reviewer;

        std::string jobName;
        std::string jobDescription;
        uint8_t state;

        uint64_t primary_key() const { return jobId;}
        uint64_t get_jobId()  const { return jobId;}

        EOSLIB_SERIALIZE(job, (jobId)(submitter)(reviewer)(jobName)(jobDescription)(state));
    };

    /// @abi table appeal i64
    typedef eosio::multi_index<N(job), job, indexed_by<N(byjobId), const_mem_fun<job, uint64_t, &job::get_jobId>> > jobs;

    jobs _job;
};

EOSIO_ABI( blockwork, (create) )




