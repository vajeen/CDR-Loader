#ifndef AERO_H
#define	AERO_H

#include "structs.h"
extern "C" {
#include <aerospike/aerospike.h>
#include <aerospike/aerospike_key.h>
#include <aerospike/as_error.h>
#include <aerospike/as_operations.h>
#include <aerospike/as_record.h>
#include <aerospike/as_status.h>
}

class aero {
public:
    aero();
    void insert(struct holder*);
    virtual ~aero();
private:
    as_config config;
    aerospike as;
    as_error err;
    as_record rec;
    as_key key;
};

#endif	/* AERO_H */

