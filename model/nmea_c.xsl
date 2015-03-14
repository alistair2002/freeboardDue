<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="text" omit-xml-declaration="yes" indent="yes"/>

  <xsl:template name="define_parsers">
	<xsl:for-each select="nmea/sentences/sentence">
	  <xsl:choose>
		<xsl:when test="data">
		  bool parse_<xsl:value-of select="@type"/>(nmea_sentence_t *ws, char *sentence)
		  {
		  	bool parsed = true;

			<xsl:variable name="nmea_type" select="@type"/>

			/* read past the type */
			char *token = strtok(sentence, ",");
			ws->type = nmea_sentence_<xsl:value-of select="@type"/>;

			printf("token %s\n", token);

			<xsl:for-each select="data">
			  if (true == parsed)
			  {
			  	  token = strtok(NULL, ",");
		
				  if (token)
				  {
				  <xsl:choose>
					<xsl:when test="'bool' = @type">
					  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/> = (0 == strcmp("A", token))?true:false;
					</xsl:when>
					<xsl:when test="'int' = @type">
					  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/> = atoi(token);
					</xsl:when>
					<xsl:when test="'hex' = @type">
					  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/> = strtol(token, NULL, 16);
					</xsl:when>
					<xsl:when test="'float' = @type">
					  ws->nmea_sentence_<xsl:value-of select="$nmea_type"/>_value.<xsl:value-of select="@name"/> = atof(token);
					</xsl:when>
					<xsl:otherwise>
					  printf("unknown type <xsl:value-of select='@type'/>\n");
					</xsl:otherwise>
				  </xsl:choose>
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

  <xsl:template name="define_model">
	static nmea_sentence_model_element_t nmea_model[] {
	<xsl:for-each select="nmea/sentences/sentence">
	  <xsl:choose>
		<xsl:when test="data">
		  {
		  "<xsl:value-of select="@type"/>",
		  nmea_sentence_<xsl:value-of select="@type"/>_parser,
		  nmea_sentence_t ws
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
#include "nmea.h"
#include <stdio.h>
#include <string.h>

typedef bool (*nmea_parse_fn)(nmea_sentence_t* ws, char *sentence);

typedef struct {
	const char *type;
	nmea_parse_fn parser;
	nmea_sentence_t ws;
} nmea_sentence_model_element_t;

]]>

	<xsl:call-template name="define_parsers"/>
	<xsl:call-template name="define_model"/>

<![CDATA[
void parse_nmea(char *sentence){
}
]]>

  </xsl:template>

</xsl:stylesheet>
