#include "aero.h"

aero::aero() {
    as_config_init(&config);
    config.hosts[0].addr = "127.0.0.1";
    config.hosts[0].port = 3000;

    aerospike_init(&as, &config);

    if (aerospike_connect(&as, &err) != AEROSPIKE_OK) {
        fprintf(stderr, "err(%d) %s at [%s:%d]\n", err.code, err.message, err.file, err.line);
    }
}

void aero::insert(struct holder *smgt) {
    //By Mobile
    as_record_inita(&rec, 2);
    //as_record_set_str(&rec, "mobile", smgt.number.c_str());
    as_record_set_str(&rec, "imsi", smgt->imsi.c_str());
    as_record_set_str(&rec, "plan", smgt->plan.c_str());

    as_key_init_str(&key, "Reports", "MOBILE", smgt->number.c_str());

    if (aerospike_key_put(&as, &err, NULL, &key, &rec) != AEROSPIKE_OK) {
        fprintf(stderr, "err(%d) %s at [%s:%d]\n", err.code, err.message, err.file, err.line);
    }
    as_record_destroy(&rec);
    
    //By IMSI
    as_record_inita(&rec, 2);
    as_record_set_str(&rec, "mobile", smgt->number.c_str());
    as_record_set_str(&rec, "plan", smgt->plan.c_str());
    
    as_key_init_str(&key, "Reports", "IMSI", smgt->number.c_str());
    if (aerospike_key_put(&as, &err, NULL, &key, &rec) != AEROSPIKE_OK) {
        fprintf(stderr, "err(%d) %s at [%s:%d]\n", err.code, err.message, err.file, err.line);
    }
    as_record_destroy(&rec);
    
    delete smgt;
}

aero::~aero() {
}

