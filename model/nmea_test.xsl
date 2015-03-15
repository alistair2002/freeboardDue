<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="text" omit-xml-declaration="yes" indent="yes"/>

  <!-- main function if you like that builds the parser -->
  <xsl:template match="/">

	<xsl:for-each select="nmea/sentences/sentence">
	  <xsl:choose>
		<xsl:when test="data">
		  ./unit_test '<xsl:value-of select="example/@value"/>'<xsl:text>&#10;</xsl:text>
		</xsl:when>
	  </xsl:choose>
	</xsl:for-each>
  </xsl:template>

</xsl:stylesheet>
