#include "Histogram.h"

//Constructor
Histogram::Histogram()
{
    m_pHistogram = new QImage( 256, 100, QImage::Format_RGB888 );
}

//Make histogram from QImage
QImage Histogram::getHistogramFromImg( QImage img )
{
    uint32_t tableR[256] = {0};
    uint32_t tableG[256] = {0};
    uint32_t tableB[256] = {0};

    //Count
    for( int y = 0; y < img.height(); y++ )
    {
        for( int x = 0; x < img.width(); x++ )
        {
            tableR[img.pixelColor(x,y).red()]++;
            tableG[img.pixelColor(x,y).green()]++;
            tableB[img.pixelColor(x,y).blue()]++;
        }
    }
    //Highest Value
    uint32_t highestVal = 0;
    for( uint8_t x = 0; x < 255; x++ )
    {
        if( tableR[x] > highestVal ) highestVal = tableR[x];
        if( tableG[x] > highestVal ) highestVal = tableG[x];
        if( tableB[x] > highestVal ) highestVal = tableB[x];
    }
    //Normalize to 100 and Paint
    m_pHistogram->fill( Qt::black );
    for( uint8_t x = 0; x < 255; x++ )
    {
        tableR[x] = tableR[x] * 100 / highestVal;
        tableG[x] = tableG[x] * 100 / highestVal;
        tableB[x] = tableB[x] * 100 / highestVal;

        for( uint32_t y = 0; y < 100; y++ )
        {
            QColor color = QColor( Qt::black );
            if( tableR[x] >= 100 - y ) color.setRed( 255 );
            if( tableG[x] >= 100 - y ) color.setGreen( 255 );
            if( tableB[x] >= 100 - y ) color.setBlue( 255 );
            m_pHistogram->setPixelColor( x, y, color );
        }
    }
    return *m_pHistogram;
}

//Make histogram from Raw Image (8bit R, 8bit G, 8bit B,...)
QImage Histogram::getHistogramFromRaw(uint8_t *m_pRawImage, uint16_t width, uint16_t height)
{
    uint32_t tableR[256] = {0};
    uint32_t tableG[256] = {0};
    uint32_t tableB[256] = {0};

    //Count
    for( int y = 0; y < height; y++ )
    {
        for( int x = 0; x < width; x++ )
        {
            tableR[ m_pRawImage[ ( ( x + ( width * y ) ) * 3 ) + 0 ] ]++;
            tableG[ m_pRawImage[ ( ( x + ( width * y ) ) * 3 ) + 1 ] ]++;
            tableB[ m_pRawImage[ ( ( x + ( width * y ) ) * 3 ) + 2 ] ]++;
        }
    }
    //Highest Value
    uint32_t highestVal = 0;
    for( uint8_t x = 0; x < 255; x++ )
    {
        if( tableR[x] > highestVal ) highestVal = tableR[x];
        if( tableG[x] > highestVal ) highestVal = tableG[x];
        if( tableB[x] > highestVal ) highestVal = tableB[x];
    }
    //Normalize to 100 and Paint
    m_pHistogram->fill( Qt::black );
    for( uint8_t x = 0; x < 255; x++ )
    {
        tableR[x] = tableR[x] * 100 / highestVal;
        tableG[x] = tableG[x] * 100 / highestVal;
        tableB[x] = tableB[x] * 100 / highestVal;

        for( uint32_t y = 0; y < 100; y++ )
        {
            QColor color = QColor( Qt::black );
            if( tableR[x] >= 100 - y ) color.setRed( 255 );
            if( tableG[x] >= 100 - y ) color.setGreen( 255 );
            if( tableB[x] >= 100 - y ) color.setBlue( 255 );
            m_pHistogram->setPixelColor( x, y, color );
        }
    }
    return *m_pHistogram;
}