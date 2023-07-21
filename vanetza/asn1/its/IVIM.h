/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "IVIM-PDU-Descriptions"
 * 	found in "asn1/TS103301v211-IVIM.asn"
 * 	`asn1c -fcompound-names -fincludes-quoted -no-gen-example -R`
 */

#ifndef	_IVIM_H_
#define	_IVIM_H_


#include "asn_application.h"

/* Including external dependencies */
#include "ItsPduHeader.h"
#include "IviStructure.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* IVIM */
typedef struct IVIM {
	ItsPduHeader_t	 header;
	IviStructure_t	 ivi;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} IVIM_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_IVIM;

#ifdef __cplusplus
}
#endif

#endif	/* _IVIM_H_ */
#include "asn_internal.h"
