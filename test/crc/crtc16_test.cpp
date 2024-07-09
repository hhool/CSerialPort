#include <iostream>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#define imsleep(microsecond) Sleep(microsecond) // ms
#else
#include <unistd.h>
#define imsleep(microsecond) usleep(1000 * microsecond) // ms
#endif

#ifndef _WIN32
#include <thread> // std::thread
#endif

#include "gtest/gtest.h"

#include "crc/crc16.h"

class CRC16Test : public testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(CRC16Test, CheckCRC16)
{
	// broadcast machin on
	{
        std::vector<uint8_t> data = {0x00, 0x05, 0x00, 0x02, 0xFF, 0x00};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0x2B2C);
	}
	// broadcast machin off
    {
        std::vector<uint8_t> data = {0x00, 0x05, 0x00, 0x02, 0x00, 0x00};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0xDB6D);
    }
    // peer machin on
    {
        std::vector<uint8_t> data = {0x01, 0x05, 0x00, 0x02, 0xFF, 0x00};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0xFA2D);
    }
    // peer machin off
    {
        std::vector<uint8_t> data = {0x01, 0x05, 0x00, 0x02, 0x00, 0x00};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0x0A6C);
    }
    // get freqence
    {
        std::vector<uint8_t> data = {0x01, 0x04, 0x00, 0x01, 0x00, 0x01};
        uint16_t crc= itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0x0A60);
    }
    // get power
    {
        std::vector<uint8_t> data = {0x01, 0x04, 0x00, 0x00, 0x00, 0x01};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0xCA31);
    }
    // get fault code
    {
        std::vector<uint8_t> data = {0x01, 0x04, 0x00, 0x02, 0x00, 0x01};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0x0A90);
    }
    // set amplitude 20%
    {
        std::vector<uint8_t> data = {0x01, 0x06, 0x00, 0x18, 0x00, 0x14};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0xC209);
    }
    // set amplitude 60%
    {
        std::vector<uint8_t> data = {0x01, 0x06, 0x00, 0x18, 0x00, 0x3C};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0xDC09);
    }
    // set amplitude of welding 80%
    {
        std::vector<uint8_t> data = {0x01, 0x06, 0x00, 0x18, 0x00, 0x50};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0xF109);
    }
    // set amplitude of welding 100%
    {
        std::vector<uint8_t> data = {0x01, 0x06, 0x00, 0x18, 0x00, 0x64};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0x2608);
    }
	// set time of welding
    {
        std::vector<uint8_t> data = {0x01, 0x06, 0x00, 0x19, 0x00, 0xC8};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0x9B59);
    }
	// set amplitude and time of welding
    {
        std::vector<uint8_t> data = {0x01, 0x10, 0x00, 0x18, 0x00, 0x02, 0x04, 0x00, 0x3C, 0x01, 0x2C};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0x4433);
    }
	// set highest freq 20200HZ
	{
        std::vector<uint8_t> data = {0x01, 0x06, 0x00, 0x03, 0x4E, 0xE8};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0x244C);
	}
	// set lowest freq 19200HZ
	{
        std::vector<uint8_t> data = {0x01, 0x06, 0x00, 0x04, 0x4B, 0x00};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0xFBFE);
	}
	// set highest and lowest freq 20200HZ 19200HZ
    {
        std::vector<uint8_t> data = {0x01, 0x10, 0x00, 0x03, 0x00, 0x02, 0x04, 0x4E, 0xE8, 0x4B, 0x00};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0x5612);
    }
	// set highest and lowest freq 36000HZ 34000HZ
    {
        std::vector<uint8_t> data = {0x01, 0x10, 0x00, 0x3, 0x00, 0x02, 0x04, 0x8C, 0xA0, 0x84, 0xD0};
        uint16_t crc = itas109::crc16(data.data(), data.size());
        EXPECT_EQ(crc, 0x94FB);
    }
    {
        std::vector<uint8_t> data_3 = {0x01, 0x84, 0x02};
        uint16_t crc = itas109::crc16(data_3.data(), data_3.size());
        EXPECT_EQ(crc, 0xC1C2);
	}
}