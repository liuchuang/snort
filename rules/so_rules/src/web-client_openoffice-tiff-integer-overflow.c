/*
This file contains two rules to share common code and data structures for detection.

alert tcp $EXTERNAL_NET $HTTP_PORTS -> $HOME_NET any (msg:"WEB-CLIENT OpenOffice TIFF file in little endian format parsing integer overflow attempt"; flow:to_client,established; content:"II|2a 00|"; metadata:policy balanced-ips drop, policy security-ips drop, service http; reference:bugtraq,25690; reference:cve,2007-2834; classtype:attempted-user;)

alert tcp $EXTERNAL_NET $HTTP_PORTS -> $HOME_NET any (msg:"WEB-CLIENT OpenOffice TIFF file in big endian format parsing integer overflow attempt"; flow:to_client,established; content:"MM|00 2a|"; metadata:policy balanced-ips drop, policy security-ips drop, service http; reference:bugtraq,25690; reference:cve,2007-2834; classtype:attempted-user;)  
 */

/*
 * Use at your own risk.
 *
 * Copyright (C) 2005-2008 Sourcefire, Inc.
 * 
 * This file is autogenerated via rules2c, by Brian Caswell <bmc@sourcefire.com>
 */

#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"
#include "so-util.h"

//#define DEBUG 1
#ifdef DEBUG
#define DEBUG_WRAP(code) code
#else
#define DEBUG_WRAP(code)
#endif

/* declare detection functions */
int ruleCVE_2007_2834eval(void *p);

/* declare rule data structures */
/* precompile the stuff that needs pre-compiled */
/* flow:established, to_client; */
static FlowFlags ruleCVE_2007_2834flow0 = 
{
    FLOW_ESTABLISHED|FLOW_TO_CLIENT
};

static RuleOption ruleCVE_2007_2834option0 =
{
    OPTION_TYPE_FLOWFLAGS,
    {
        &ruleCVE_2007_2834flow0
    }
};

static CursorInfo ruleCVE_2007_2834file_data1 =
{
    0, /* offset */
    CONTENT_BUF_NORMALIZED /* flags */
};

// file_data;
static RuleOption ruleCVE_2007_2834option1 =
{
#ifndef MISSINGFILEDATA
    OPTION_TYPE_FILE_DATA,
#else 
    OPTION_TYPE_SET_CURSOR,
#endif
    {
        &ruleCVE_2007_2834file_data1 
    }
};

// content:"II*|00|", depth 4; 
static ContentInfo rule15975content1 = 
{
    (u_int8_t *) "II*|00|", /* pattern (now in snort content format) */
    4, /* depth */
    0, /* offset */
    CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15975option2 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule15975content1
    }
};
// content:"MM|00|*", depth 4; 
static ContentInfo rule15976content1 = 
{
    (u_int8_t *) "MM|00|*", /* pattern (now in snort content format) */
    4, /* depth */
    0, /* offset */
    CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15976option2 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule15976content1
    }
};
/* references for sid 15975 */
/* reference: bugtraq "25690"; */
static RuleReference ruleCVE_2007_2834ref1 = 
{
    "bugtraq", /* type */
    "25690" /* value */
};

/* reference: cve "2007-2834"; */
static RuleReference ruleCVE_2007_2834ref2 = 
{
    "cve", /* type */
    "2007-2834" /* value */
};

static RuleReference *ruleCVE_2007_2834refs[] =
{
    &ruleCVE_2007_2834ref1,
    &ruleCVE_2007_2834ref2,
    NULL
};

/* metadata for sid 15975 and 15976*/
/* metadata:service http, policy balanced-ips drop, policy security-ips drop; */
static RuleMetaData ruleCVE_2007_2834service1 = 
{
    "service http"
};


static RuleMetaData ruleCVE_2007_2834policy1 = 
{
    "policy balanced-ips drop"
};

static RuleMetaData ruleCVE_2007_2834policy2 = 
{
    "policy security-ips drop"
};


static RuleMetaData *ruleCVE_2007_2834metadata[] =
{
    &ruleCVE_2007_2834service1,
    &ruleCVE_2007_2834policy1,
    &ruleCVE_2007_2834policy2,
    NULL
};

RuleOption *rule15975options[] =
{
    &ruleCVE_2007_2834option0,   // common part
    &ruleCVE_2007_2834option1,
    &rule15975option2,
    NULL
};

Rule rule15975 = {
   
   /* rule header, akin to => tcp any any -> any any               */{
       IPPROTO_TCP, /* proto */
       "$EXTERNAL_NET", /* SRCIP     */
       "$HTTP_PORTS", /* SRCPORT   */
   
       0, /* DIRECTION */
       "$HOME_NET", /* DSTIP     */
   
       "any", /* DSTPORT   */
   },
   /* metadata */
   { 
       3,  /* genid (HARDCODED!!!) */
       15975, /* sigid */
       4, /* revision */
   
       "attempted-user", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
       "WEB-CLIENT OpenOffice TIFF file in little endian format parsing integer overflow attempt",     /* message */
       ruleCVE_2007_2834refs /* ptr to references */
       ,ruleCVE_2007_2834metadata
   },
   rule15975options, /* ptr to rule options */
   &ruleCVE_2007_2834eval, /* DO NOT use the built in detection function */
   0 /* am I initialized yet? */
};

RuleOption *rule15976options[] =
{
    &ruleCVE_2007_2834option0,   // common part
    &ruleCVE_2007_2834option1,
    &rule15976option2,
    NULL
};

Rule rule15976 = {
   
   /* rule header, akin to => tcp any any -> any any               */{
       IPPROTO_TCP, /* proto */
       "$EXTERNAL_NET", /* SRCIP     */
       "$HTTP_PORTS", /* SRCPORT   */
   
       0, /* DIRECTION */
       "$HOME_NET", /* DSTIP     */
   
       "any", /* DSTPORT   */
   },
   /* metadata */
   { 
       3,  /* genid (HARDCODED!!!) */
       15976, /* sigid */
       4, /* revision */
   
       "attempted-user", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
       "WEB-CLIENT OpenOffice TIFF file in big endian format parsing integer overflow attempt",     /* message */
       ruleCVE_2007_2834refs /* ptr to references */
       ,ruleCVE_2007_2834metadata
   },
   rule15976options, /* ptr to rule options */
   &ruleCVE_2007_2834eval, /* DO NOT use the built in detection function */
   0 /* am I initialized yet? */
};

/* detection functions */
int ruleCVE_2007_2834eval(void *p) {
    const u_int8_t *cursor_normal = 0;
    SFSnortPacket *sp = (SFSnortPacket *) p;
    const u_int8_t *beg_of_payload, *end_of_payload;
    const u_int8_t *cursor_start;          // pointer to the beginning of the TIFF file
    const u_int8_t *cursor_IFD_table;      // pointer to the current IFD table 
    const u_int8_t *cursor_IFD_entry;      // pointer to IFD entry to inspect
    const u_int8_t *cursor_temp;
    u_int32_t       offset_IFD_table;      // offset to the next IFD table    
    u_int16_t       num_IFD_entry;         // number of IFD entries in a table
    u_int16_t       i;
    u_int32_t       data_count;            // the size of buffer = data_count * 4. if data_count >= 0x400000, malicious packet    
    u_int16_t       tag_ID;
    
    u_int32_t (* fn_read32)(const u_int8_t *p);
    u_int16_t (* fn_read16)(const u_int8_t *p);
      
    if(sp == NULL)
        return RULE_NOMATCH;

    if(sp->payload == NULL)
        return RULE_NOMATCH;
    
    // flow:established, to_client;
    if (checkFlow(p, ruleCVE_2007_2834option0.option_u.flowFlags) > 0 ) {

        // file_data;
        #ifndef MISSINGFILEDATA
        if (fileData(p, rule15975options[1]->option_u.cursor, &cursor_normal) <= 0) 
            return RULE_NOMATCH;
        #else
        if (setCursor(p, rule15975options[1]->option_u.cursor, &cursor_normal) <= 0)
            return RULE_NOMATCH;
        #endif

        // content:"II*|00|", depth 4; // little endian format
        if (contentMatch(p, rule15975options[2]->option_u.content, &cursor_normal) > 0)
        {
            fn_read32 = &read_little_32;
            fn_read16 = &read_little_16;
            DEBUG_WRAP(printf("II|2a 00| matched\n");)
        } // content:"MM|00|*", depth 4;  // big endian format
        else if (contentMatch(p, rule15976options[2]->option_u.content, &cursor_normal) > 0)
        {
            fn_read32 = &read_big_32;
            fn_read16 = &read_big_16;
            DEBUG_WRAP(printf("MM|00 2a| matched\n");)
        }
        else
        {
            DEBUG_WRAP(printf("No pattern is matched\n");)
            return RULE_NOMATCH;
        }
        
        if(getBuffer(sp, CONTENT_BUF_NORMALIZED, &beg_of_payload, &end_of_payload) <= 0)
           return RULE_NOMATCH;

        cursor_start = cursor_normal - 4; 

        while (cursor_normal + 4 <= end_of_payload)
        {               
            offset_IFD_table = (*fn_read32)(cursor_normal);   // read the first IFD offset
            cursor_IFD_table = cursor_start + offset_IFD_table;

            DEBUG_WRAP(printf("offset_IFD_table = 0x%08x\n", offset_IFD_table);)
            
            if (cursor_IFD_table <= cursor_start)             // check if there is an integer overflow
                return RULE_NOMATCH;                  

            if (cursor_IFD_table + 2 > end_of_payload)       // break if cursor reaches to the end of paylaod
                return RULE_NOMATCH;
            
            num_IFD_entry = (*fn_read16)(cursor_IFD_table);  // get the number of IFD entries in a table
            cursor_IFD_entry = cursor_IFD_table + 2;           // pointer to the first IFD entry

            DEBUG_WRAP(printf("num_IFD_entry = 0x%04x\n", num_IFD_entry);)
            
            for (i = 0; i < num_IFD_entry; i++) // loop for num_IFD_entry times and until the cursor is valid
            {
                if (cursor_IFD_entry + 8 > end_of_payload)
                    return RULE_NOMATCH;

                tag_ID = (*fn_read16)(cursor_IFD_entry);                  
                DEBUG_WRAP(printf("Tag ID : 0x%04x\n", tag_ID);)
                  
                if (tag_ID == 0x0111 || tag_ID == 0x0117)
                {
                    cursor_IFD_entry += 4;    // move the cursor to point Data Count field
                    data_count = (*fn_read32)(cursor_IFD_entry);
                    DEBUG_WRAP(printf("data_count : 0x%08x\n", data_count);)
                    
                    if (data_count >= 0x40000000) // malicious condition
                        return RULE_MATCH;

                    cursor_IFD_entry += 8;
                }
                else
                {
                    cursor_IFD_entry += 12;
                }
            }

            cursor_temp = cursor_IFD_table + 2 + (12 * num_IFD_entry);   // pointer to the offset for the next OFD table
            
            if (cursor_normal < cursor_temp)       // check if there is an integer overflow
                cursor_normal = cursor_temp; 
            else
                return RULE_NOMATCH;                                                 
        }
    } 

    return RULE_NOMATCH;    
}
