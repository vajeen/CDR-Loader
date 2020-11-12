/* 
 * File:   instances.h
 * Author: vajeenk
 *
 * Created on August 29, 2016, 8:55 AM
 */

#ifndef INSTANCES_H
#define	INSTANCES_H

#ifdef	__cplusplus
extern "C" {
#endif

static sql::Driver *driver = get_driver_instance();


#ifdef	__cplusplus
}
#endif

#endif	/* INSTANCES_H */

