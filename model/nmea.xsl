<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="text" omit-xml-declaration="yes" indent="yes"/>

<!-- this template builds the type definitions for the structure members -->
<xsl:template name="build_elements">
  <xsl:for-each select="data">
	<xsl:choose>
	  <xsl:when test="@marker"/><!-- if it is a marker we don't need an allocation -->
	  <xsl:when test="'hex' = @type">
		<xsl:text>uint32_t </xsl:text><xsl:value-of select="@name"/>;
	  </xsl:when>
	  <xsl:when test="'hex' = @type">
		<xsl:text>uint32_t </xsl:text><xsl:value-of select="@name"/>;
	  </xsl:when>
	  <xsl:when test="'int' = @type">
		<xsl:text>uint32_t </xsl:text><xsl:value-of select="@name"/>;
	  </xsl:when>
	  <xsl:otherwise>
		<xsl:value-of select="@type"/><xsl:text> </xsl:text><xsl:value-of select="@name"/>;
	  </xsl:otherwise>
	</xsl:choose>
  </xsl:for-each>
</xsl:template>
  
<!-- this template builds the commonly used types like time and date -->
  <xsl:template name="define_types">
	/* types */
	<xsl:for-each select="nmea/types/type">
	  /* type <xsl:value-of select="@name"/> - <xsl:value-of select="@desc"/> */
	  typedef struct {
	  <xsl:call-template name="build_elements"/>
	  } <xsl:value-of select="@name"/>_T
	</xsl:for-each>
  </xsl:template>

<!-- this template builds the nmea structures -->
  <xsl:template name="define_structs">
	/* nmea objects */
	<xsl:for-each select="nmea/sentences/sentence">
	  /* <xsl:value-of select="@type"/> - <xsl:value-of select="@desc"/> */
	  typedef struct {
	  <xsl:call-template name="build_elements"/>
	  } <xsl:value-of select="@type"/>_T;
	</xsl:for-each>
	<xsl:text>&#10;</xsl:text>
  </xsl:template>

  <!-- main function if you like that builds the parser -->
  <xsl:template match="/">

	<xsl:call-template name="define_types"/>

	<xsl:call-template name="define_structs"/>

  </xsl:template>
</xsl:stylesheet>
