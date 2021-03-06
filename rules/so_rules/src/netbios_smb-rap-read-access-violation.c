/*
 * Vuln Title: XXXX
 *
 * Copyright (C) 2005-2010 Sourcefire, Inc. All Rights Reserved
 *
 * Written by XXXX, Sourcefire VRT <XXXX@sourcefire.com>
 *
 * Auto-generated by XXXX
 *
 * This file may contain proprietary rules that were created, tested and
 * certified by Sourcefire, Inc. (the "VRT Certified Rules") as well as
 * rules that were created by Sourcefire and other third parties and
 * distributed under the GNU General Public License (the "GPL Rules").  The
 * VRT Certified Rules contained in this file are the property of
 * Sourcefire, Inc. Copyright 2005 Sourcefire, Inc. All Rights Reserved.
 * The GPL Rules created by Sourcefire, Inc. are the property of
 * Sourcefire, Inc. Copyright 2002-2005 Sourcefire, Inc. All Rights
 * Reserved.  All other GPL Rules are owned and copyrighted by their
 * respective owners (please see www.snort.org/contributors for a list of
 * owners and their respective copyrights).  In order to determine what
 * rules are VRT Certified Rules or GPL Rules, please refer to the VRT
 * Certified Rules License Agreement.
 */

#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"

//#define DEBUG
#ifdef DEBUG
#define DEBUG_SO(code) code
#else
#define DEBUG_SO(code)
#endif

#ifndef READ_BIG_16
#define READ_BIG_16(p) ((*((u_int8_t *)(p)) << 8) \
                | (*((u_int8_t *)(p + 1))))
#endif

#ifndef READ_LITTLE_16
#define READ_LITTLE_16(p) (*((u_int8_t *)(p) + 1) << 8) \
                | (*(p))
#endif


/* declare detection functions */
int rule23847eval(void *p);

/* declare rule data structures */
/* flow:established, to_client; */
static FlowFlags rule23847flow0 = 
{
    FLOW_ESTABLISHED|FLOW_TO_CLIENT
};

static RuleOption rule23847option0 =
{
    OPTION_TYPE_FLOWFLAGS,
    {
        &rule23847flow0
    }
};
// content:"|FF|SMB|25|", depth 0, fast_pattern; 
static ContentInfo rule23847content1 = 
{
    (u_int8_t *) "|FF|SMB|25 00 00 00 00|", /* pattern (now in snort content format) */
    9, /* depth */
    4, /* offset */
    CONTENT_FAST_PATTERN|CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule23847option1 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule23847content1
    }
};
// content:"|EA 00|", offset 47, depth 2, relative; 
static ContentInfo rule23847content2 = 
{
    (u_int8_t *) "|EA 00|", /* pattern (now in snort content format) */
    2, /* depth */
    47, /* offset */
    CONTENT_RELATIVE|CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule23847option2 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule23847content2
    }
};

/* references for sid 23847 */
/* reference: cve "2012-1667"; */
static RuleReference rule23847ref1 =
{
    "cve", /* type */
    "2012-1850" /* value */
};

/* reference: url "technet.microsoft.com/en-us/security/bulletin/MS12-054"; */
static RuleReference rule23847ref2 =
{
    "url", /* type */
    "technet.microsoft.com/en-us/security/bulletin/MS12-054" /* value */
};

static RuleReference *rule23847refs[] =
{
    &rule23847ref1,
    &rule23847ref2,
    NULL
};
/* metadata for sid 23847 */
/* metadata:service netbios-ssn; */
static RuleMetaData rule23847service1 = 
{
    "service netbios-ssn"
};



static RuleMetaData *rule23847metadata[] =
{
    &rule23847service1,
    NULL
};

RuleOption *rule23847options[] =
{
    &rule23847option0,
    &rule23847option1,
    &rule23847option2,
    NULL
};

Rule rule23847 = {
   /* rule header, akin to => tcp any any -> any any */
   {
       IPPROTO_TCP, /* proto */
       "$EXTERNAL_NET", /* SRCIP     */
       "[139,445]", /* SRCPORT   */
       0, /* DIRECTION */
       "$HOME_NET", /* DSTIP     */
       "any", /* DSTPORT   */
   },
   /* metadata */
   { 
       3,  /* genid */
       23847, /* sigid */
       2, /* revision */
       "attempted-admin", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
       "NETBIOS MS-RAP NetServerEnum2 read access violation attempt",     /* message */
       rule23847refs, /* ptr to references */
       rule23847metadata
   },
   rule23847options, /* ptr to rule options */
   &rule23847eval, /* use the built in detection function */
   0 /* am I initialized yet? */
};


/* detection functions */
int rule23847eval(void *p) {
    const u_int8_t *cursor_normal = 0;
    SFSnortPacket *sp = (SFSnortPacket *) p;
    const u_int8_t *end_of_payload = 0;
    const u_int8_t *beg_of_payload = 0;
    const u_int8_t *beg_of_servers = 0;
    const u_int8_t *start_of_smb = 0;

    int16_t converter = 0;
    int16_t server_comment = 0;
    int16_t server_comment_position = 0;

    u_int32_t entries = 0;
    u_int32_t netbios_message_length = 0; 

    int i;

    if(sp == NULL)
        return RULE_NOMATCH;

    if(sp->payload == NULL)
        return RULE_NOMATCH;
    
    // flow:established, to_client;
    if (checkFlow(p, rule23847options[0]->option_u.flowFlags) <= 0 )
      return RULE_NOMATCH;

    // Verify we are looking at an SMB Trans (0x25) response.
    // Verify the SMB Request was STATUS_SUCCESS (0x00000000)
    // content:"|FF|SMB|25 00 00 00 00|", depth 0, fast_pattern;
    if (contentMatch(p, rule23847options[1]->option_u.content, &cursor_normal) <= 0)
      return RULE_NOMATCH;

    // Verify LANMAN protocol is reporting additional data available.
    // content:"|EA 00|", offset 47, depth 2, relative;
    if(contentMatch(p, rule23847options[2]->option_u.content, &cursor_normal) <= 0)
      return RULE_NOMATCH;

    // Get the beginning of payload and end of payload positions.
    if(getBuffer(sp, CONTENT_BUF_NORMALIZED, &beg_of_payload, &end_of_payload) <= 0)
      return RULE_NOMATCH;

    start_of_smb = beg_of_payload + 4;  // Beginning of 9-byte content match

    netbios_message_length = READ_BIG_16(beg_of_payload + 2); // 2 byte size field
    DEBUG_SO(fprintf(stderr,"\nnetbios_message_length: %d\n", netbios_message_length);)
    DEBUG_SO(fprintf(stderr, "start_of_smb + netbios_message_length: %p\n", start_of_smb + netbios_message_length);)

    // Verify we have data to read for mutiplier and start of servers field.
    // remember, we are after the |EA 00| match above for LANMAN protocol
    if((cursor_normal + 29) > end_of_payload)
      return RULE_NOMATCH;

    // Read in the mutiplier (called "Convert" in the protocol) we will use
    // this value later to calculate the indicated server comment position.
    converter = READ_LITTLE_16(cursor_normal);
    DEBUG_SO(fprintf(stderr,"converter: %d\n",converter);)
    cursor_normal += 2;

    // Account for default converter offset
    // observed in live MS-RAP traffic
    if(converter == 0)
      converter = 0x45;

    // Read in the server entry count.
    entries = READ_LITTLE_16(cursor_normal);
    DEBUG_SO(fprintf(stderr,"number of entries: %d\n",entries);)

    // Store the position of the servers entry array. We will use
    // this later to calculate the indicated server comment position.
    // Note we do not increment cursor_normal because it turns out we are
    // perfectly lined up for reading what we need already.
    beg_of_servers = cursor_normal + 4;

    // Now we need to loop through each entry in the server entry array to check
    // for the vulnerability condition i.e. if the indicated server comment position
    // is beyond the SMB message length.

    // Limit the number of checks we'll do
    if(entries > 20)
       entries = 20;

    for(i = 0; i < entries; i++) {

      // Verify we have a server comment position (2 byte field) to read.
      if((cursor_normal + 27) > end_of_payload)
        return RULE_NOMATCH;

      DEBUG_SO(fprintf(stderr,"Entry: %d\n", i+1);)

      // Set the cursor to the server comment field.
      cursor_normal += 26; // each record is 26 bytes long.

      // Read the server comment base position.
      server_comment = READ_LITTLE_16(cursor_normal);
      DEBUG_SO(fprintf(stderr, "server_comment: %d\n", server_comment);)

      // Calculate the server comment position relative to the beginning of the server entry array.
      server_comment_position = server_comment - converter;
      DEBUG_SO(fprintf(stderr, "beg_of_servers + server_comment_position > start_of_smb + netbios_message_length ?");)
      DEBUG_SO(fprintf(stderr, " %p > %p\n", (beg_of_servers + server_comment_position), (start_of_smb + netbios_message_length));)

      // If the absolute server comment position (beginning of servers array + relative server comment position)
      // is beyond the smb message length the vulnerability condition has been met.
      if((beg_of_servers + server_comment_position) > (start_of_smb + netbios_message_length))
        return RULE_MATCH;
    }

    return RULE_NOMATCH;
}
/*
Rule *rules[] = {
    &rule23847,
    NULL
};
*/
