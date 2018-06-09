#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <time.h>

using namespace eosio;

class blockwork : public eosio::contract {

public:
    typedef enum {
        OPENED = 0,
        COMPLETED = 1,
        REJECTED = 2,
        PAID = 3
    } State;

    blockwork(account_name s) : contract(s), _job(s, s) {
    }

    /// @abi action
    void create(account_name submitter,
                uint64_t jobId,
                std::string jobName,
                std::string jobDescription,
                std::string price) {
        require_auth(submitter);

        eosio_assert(_job.find(jobId) == _job.end(), "This jobId already exists in the addressbook");

        _job.emplace(get_self(), [&]( auto& j ) {
           j.jobId = jobId;
           j.submitter = submitter;
           j.jobName = jobName;
           j.jobDescription = jobDescription;
           j.state = OPENED;
           j.reviewer = 0;
           j.price = price;
           //@FIXME
           j.creationTime = 0;
        });               
    }

    /// @abi action
    void markcomplete(account_name reviewer, uint64_t jobId) {
        require_auth(reviewer);

        auto record = _job.find(jobId);
        eosio_assert(record != _job.end(), "Couldn't get the job.");

        _job.modify(record, reviewer, [&](auto &j) {
            j.reviewer = reviewer;
            j.state = COMPLETED;
        });
    }

private:

    /// @abi table job
    struct job {
        uint64_t jobId;
        account_name submitter;
        account_name reviewer;

        std::string jobName;
        std::string jobDescription;
        std::string price;
        uint8_t state;

        uint64_t creationTime;

        uint64_t primary_key() const { return jobId;}
        uint64_t get_jobId()  const { return jobId;}

        EOSLIB_SERIALIZE(job, (jobId)(submitter)(reviewer)(jobName)(jobDescription)(state)(price)(creationTime));
    };

    /// @abi table appeal i64
    typedef eosio::multi_index<N(job), job, indexed_by<N(byjobId), const_mem_fun<job, uint64_t, &job::get_jobId>> > jobs;

    jobs _job;
};

EOSIO_ABI( blockwork, (create)(markcomplete) )




