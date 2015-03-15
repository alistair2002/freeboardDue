<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="text" omit-xml-declaration="yes" indent="yes"/>

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
						printf("unknown type <xsl:value-of select='@type'/>\n");
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
		  printf("type %d\n", ws->type);
			<xsl:variable name="nmea_type" select="@type"/>
			<xsl:for-each select="data">
			  <xsl:choose>
				<xsl:when test="@marker"/> <!-- exclude non-entities -->
				<xsl:when test="'bool' = @type">
				  printf("<xsl:value-of select="@name"/> = (%s)\n", 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>?"true":"false");
				</xsl:when>
				<xsl:when test="'int' = @type">
				  printf("<xsl:value-of select="@name"/> = (%i)\n", 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>);
				</xsl:when>
				<xsl:when test="'hex' = @type">
				  printf("<xsl:value-of select="@name"/> = (%8.8x)\n", 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>);
				</xsl:when>
				<xsl:when test="'float' = @type">
				  printf("<xsl:value-of select="@name"/> = (%f)\n", 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>);
				</xsl:when>
				<xsl:when test="'char' = @type">
				  printf("<xsl:value-of select="@name"/> = (%c)\n", 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>);
				</xsl:when>
				<xsl:when test="'nmea_string' = @type">
				  printf("<xsl:value-of select="@name"/> = (%s)\n", 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.buffer);
				</xsl:when>
				<xsl:when test="'nmea_time' = @type">
				  printf("<xsl:value-of select="@name"/> = (%2.2d:%2.2d:%2.2d.%2.2d)\n", 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.hours, 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.minutes, 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.seconds, 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.centiseconds);
				</xsl:when>
				<xsl:when test="'nmea_date' = @type">
				  printf("<xsl:value-of select="@name"/> = (%2.2d/%2.2d/%2.2d)\n", 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.day, 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.month, 
				  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/>.year);
				</xsl:when>
				<xsl:otherwise>
				  printf("unknown type <xsl:value-of select='@type'/>\n");
				</xsl:otherwise>
			  </xsl:choose>
			</xsl:for-each><!-- data -->
			}
		</xsl:when>
	  </xsl:choose>
	</xsl:for-each>
  </xsl:template>

  <xsl:template name="define_model">
	static nmea_sentence_model_element_t nmea_model[] {
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

  <!-- main function if you like that builds the parser -->
  <xsl:template match="/">

<!-- dump this bit straight out -->
<![CDATA[
#include "autogen_nmea.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

<![CDATA[
#define DIM(a) (sizeof(a)/sizeof(*a))

void parse_nmea(const char *sentence){
	if ('$' == *sentence)
	{
		unsigned int i = 1;
		const char *key = sentence+1;

		while (key[i] && (',' != key[i]) && ('*' != key[i])) i++;

		printf("key size (%d)\n", i);

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

						printf("==\n");

						nmea_model[mdl].to_string(&nmea_model[mdl].ws);
					}
				}
			}
		}
	}
}
]]>

  </xsl:template>

</xsl:stylesheet>
