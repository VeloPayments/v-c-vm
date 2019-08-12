#ifndef VCVM_STACK_CERT_H
#define VCVM_STACK_CERT_H

#include <vccert/parser.h>

typedef struct vcvm_stack_cert
{
    disposable_t hdr;
    allocator_options_t* allocator_options;
    vccert_parser_context_t* parser_context;
    vccert_parser_options_t* parser_options;
} vcvm_stack_cert_t;

int vcvm_stack_cert_init(vcvm_stack_cert_t* cert, allocator_options_t* allocator_options, vccert_parser_options_t* parser_options);

#endif  //VCVM_STACK_CERT_H
