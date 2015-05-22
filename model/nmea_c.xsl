<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="text" omit-xml-declaration="yes" indent="yes"/>

  <xsl:template name="define_names">
	typedef enum {
		nmea_sentence_invalid,
 		<xsl:for-each select="nmea/sentences/sentence">
 		  <xsl:choose>
 			<xsl:when test="data">
			  nmea_sentence_<xsl:value-of select="@type"/>,
 			</xsl:when>
 		  </xsl:choose>
 		</xsl:for-each>
		} nmea_sentence_names_t;
  </xsl:template>

  <xsl:template name="define_union">
	typedef struct {
		nmea_sentence_names_t type;
		union {
		<xsl:for-each select="nmea/sentences/sentence">
		  <xsl:choose>
			<xsl:when test="data">
			  <xsl:value-of select="@type"/>_T nmea_sentence_<xsl:value-of select="@type"/>_value;
			</xsl:when>
		  </xsl:choose>
		</xsl:for-each>
		};
	} nmea_sentence_t;
  </xsl:template>

  <xsl:template name="define_parsers">
	<xsl:for-each select="nmea/sentences/sentence">
	  <xsl:choose>
		<xsl:when test="data">
		  bool parse_<xsl:value-of select="@type"/>(nmea_sentence_t *ws, const char* next)
		  {
		  	bool parsed = true;

			<xsl:variable name="nmea_type" select="@type"/>
			<xsl:variable name="nmea_elements" select="count(data)"/>
			ws->type = nmea_sentence_<xsl:value-of select="@type"/>;

			<xsl:for-each select="data">
			  if (true == parsed)
			  {
			  	  const char *token = next;

		
				  if (token)
				  {
				  <![CDATA[
				  	/* look for the end of the bit */
     				while ((*next) && (',' != *next) && ('*' != *next)) next++;
				  ]]>
					<xsl:choose>
					  <xsl:when test="@marker"/> <!-- exclude non-entities -->
					  <xsl:when test="'bool' = @type">
						ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/> = ('A' == *token)?true:false;
					  </xsl:when>
					  <xsl:when test="'int' = @type">
						ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/> = strtol(token, NULL, 10);
					  </xsl:when>
					  <xsl:when test="'hex' = @type">
						ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/> = strtol(token, NULL, 16);
					  </xsl:when>
					  <xsl:when test="'float' = @type">
						ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/> = strtod(token, NULL);
					  </xsl:when>
					  <xsl:when test="'char' = @type">
						ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/> = (next==token)?'V':*token;
					  </xsl:when>
					  <xsl:when test="'nmea_string' = @type">
						parse_nmea_string(&amp;ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>, token);
					  </xsl:when>
					  <xsl:when test="'nmea_time' = @type">
						parse_nmea_time(&amp;ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>, token);
					  </xsl:when>
					  <xsl:when test="'nmea_date' = @type">
						parse_nmea_date(&amp;ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>, token);
					  </xsl:when>
					  <xsl:otherwise>
						debug_printf("unknown type <xsl:value-of select='@type'/>\r\n");
					  </xsl:otherwise>
					</xsl:choose>

					if (*next) next++;
				  }
				  else
				  {
				  parsed = false;
				  }
			  }
			</xsl:for-each><!-- data -->
				return parsed;
			}
		</xsl:when>
	  </xsl:choose>
	</xsl:for-each>
  </xsl:template>

  <xsl:template name="define_dumpers">
	<xsl:for-each select="nmea/sentences/sentence">
	  <xsl:choose>
		<xsl:when test="data">
		  void dump_<xsl:value-of select="@type"/>(nmea_sentence_t *ws)
		  {
			<xsl:variable name="nmea_type" select="@type"/>
			<xsl:for-each select="data">
			  <xsl:choose>
				<xsl:when test="@marker"/> <!-- exclude non-entities -->
				<xsl:when test="'bool' = @type">
				  debug_printf("<xsl:value-of select="@name"/> = (%s)\r\n", 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>?"true":"false");
				</xsl:when>
				<xsl:when test="'int' = @type">
				  debug_printf("<xsl:value-of select="@name"/> = (%i)\r\n", 
				  (int)ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>);
				</xsl:when>
				<xsl:when test="'hex' = @type">
				  debug_printf("<xsl:value-of select="@name"/> = (%8.8x)\r\n", 
				  (int)ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>);
				</xsl:when>
				<xsl:when test="'float' = @type">
				  debug_printf("<xsl:value-of select="@name"/> = (%f)\r\n", 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>);
				</xsl:when>
				<xsl:when test="'char' = @type">
				  debug_printf("<xsl:value-of select="@name"/> = (%c)\r\n", 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>);
				</xsl:when>
				<xsl:when test="'nmea_string' = @type">
				  debug_printf("<xsl:value-of select="@name"/> = (%s)\r\n", 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.buffer);
				</xsl:when>
				<xsl:when test="'nmea_time' = @type">
				  debug_printf("<xsl:value-of select="@name"/> = (%2.2d:%2.2d:%2.2d.%2.2d)\r\n", 
				  (int)ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.hours, 
				  (int)ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.minutes, 
				  (int)ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.seconds, 
				  (int)ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.centiseconds);
				</xsl:when>
				<xsl:when test="'nmea_date' = @type">
				  debug_printf("<xsl:value-of select="@name"/> = (%2.2d/%2.2d/%2.2d)\r\n", 
				  (int)ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.day, 
				  (int)ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.month, 
				  (int)ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.year);
				</xsl:when>
				<xsl:otherwise>
				  debug_printf("unknown type <xsl:value-of select='@type'/>\r\n");
				</xsl:otherwise>
			  </xsl:choose>
			</xsl:for-each><!-- data -->
			}
		</xsl:when>
	  </xsl:choose>
	</xsl:for-each>
  </xsl:template>

  <xsl:template name="define_model">
	/* autogenerated array size plus one for the null element */
	static nmea_sentence_model_element_t nmea_model[<xsl:value-of select="count(nmea/sentences/sentence[data])"/> + 1] {
		{/* null element to pair with invalid enumeration */},
	<xsl:for-each select="nmea/sentences/sentence">
	  <xsl:choose>
		<xsl:when test="data">
		  {
		  "<xsl:value-of select="@type"/>",
		  parse_<xsl:value-of select="@type"/>,
		  dump_<xsl:value-of select="@type"/>,
		  {}
		  },
		</xsl:when>
	  </xsl:choose>
	</xsl:for-each>
	};
  </xsl:template>

  <xsl:template name="define_getters">
	<xsl:for-each select="nmea/sentences/sentence">
	  <xsl:choose>
		<xsl:when test="data">
<xsl:value-of select="@type"/>_T *Model::get_<xsl:value-of select="@type"/>(void) const
{
 return &amp;nmea_model[nmea_sentence_<xsl:value-of select="@type"/>].ws.nmea_sentence_<xsl:value-of select="@type"/>_value;
}
		</xsl:when>
	  </xsl:choose>
	</xsl:for-each>
  </xsl:template>

  <!-- main function if you like that builds the parser -->
  <xsl:template match="/">

<!-- dump this bit straight out -->
<![CDATA[
#ifdef ARDUINO
#include "Arduino.h"
#endif
#include "nmea_model.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//#define DEBUG 1

#ifdef DEBUG
#define DEBUG_PRINTF 1
#else
#define DEBUG_PRINTF 0
#endif

#ifdef ARDUINO
char buffer[1024];
#define debug_printf( args, ... ) do { if (DEBUG_PRINTF) { sprintf(buffer, args, ## __VA_ARGS__ ); Serial.print(buffer);} } while(0);
#else
#define debug_printf( args, ... ) do { if (DEBUG_PRINTF) printf( args, ## __VA_ARGS__ ); } while(0);
#endif

]]>

	<xsl:call-template name="define_names"/>
	<xsl:call-template name="define_union"/>

<![CDATA[

extern bool parse_nmea_date( nmea_date *date, const char *buffer );
extern bool parse_nmea_time( nmea_time *time, const char *buffer );
extern bool parse_nmea_string( nmea_string *time, const char *buffer );

typedef bool (*nmea_parse_fn)(nmea_sentence_t* ws, const char *sentence);
typedef void (*nmea_string_fn)(nmea_sentence_t* ws);

typedef struct {
	const char *type;
	nmea_parse_fn parser;
	nmea_string_fn to_string;
	nmea_sentence_t ws;
} nmea_sentence_model_element_t;

]]>

	<xsl:call-template name="define_parsers"/>
	<xsl:call-template name="define_dumpers"/>
	<xsl:call-template name="define_model"/>
	<xsl:call-template name="define_getters"/>

<![CDATA[

#define DIM(a) (sizeof(a)/sizeof(*a))

Model::Model( void )
{
	// constructor
}

Model::~Model( void )
{
	// destructor
}

void Model::parse_nmea(const char *sentence){
	if ('$' == *sentence)
	{
		unsigned int i = 1;
		const char *key = sentence+1;

		while (key[i] && (',' != key[i]) && ('*' != key[i])) i++;

		debug_printf("%s", sentence);

		if ((key[i]) && (5 == i))
		{
			unsigned mdl = 0;
			i++; /* get past seperator */
			
			for (mdl=1; mdl< DIM(nmea_model); mdl++)
			{
				/* avoiding the '$GP' */
				if (0 == strncmp(sentence+3, nmea_model[mdl].type, 3))
				{
					nmea_sentence_t ws = {};

					/* sentence is passed in the magic of strtok */
					if (nmea_model[mdl].parser(&ws, key+i))
					{
						/* perform the magic update */
						memcpy(&nmea_model[mdl].ws, &ws, sizeof(ws));
#ifdef DEBUG
						debug_printf("\r\n==\r\n");
						nmea_model[mdl].to_string(&nmea_model[mdl].ws);
#endif
					}
				}
			}
		}
	}
}
]]>

  </xsl:template>

</xsl:stylesheet>
