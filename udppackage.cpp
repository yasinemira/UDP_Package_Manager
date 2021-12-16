#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include <QDebug>
#include <QString>

#include "udppackage.h"

static constexpr int ethernetFramelength = 20;
static constexpr int ipv4HeaderLength = 14;
static constexpr int udpHeaderLength = 8;

static int currentPackageNumber = 0;

UdpPackage::UdpPackage(QObject *parent)
    : QObject(parent)
{
    ++currentPackageNumber;
    std::cout << "\nPackage creation for #" << currentPackageNumber << " requested....." << std::endl;
}

UdpPackage::~UdpPackage()
{
    std::cout << "\nPackage termination for #" << currentPackageNumber << " requested....." << std::endl;
    --currentPackageNumber;
}

UdpPackage::UdpPackage(char* ethernetPacket, int packetLength)
{
    setMainPacket(ethernetPacket, packetLength);
    setEthernetFrameHeader(ethernetPacket, packetLength);
    setIpv4Header(ethernetPacket);
    setIpv4HeaderChecksum();
    setSourceIPAdress();
    setDestinationIPAdress();
    setUdpHeader(ethernetPacket);
    setSourcePort();
    setDestinationPort();
    setUdpChecksum();
    setPayload(ethernetPacket, packetLength);
}

void UdpPackage::displayPackageDetails(char* ethernetPacket, int packetLength)
{
    setMainPacket(ethernetPacket, packetLength);
    setEthernetFrameHeader(ethernetPacket, packetLength);
    setIpv4Header(ethernetPacket);
    setIpv4HeaderChecksum();
    setSourceIPAdress();
    setDestinationIPAdress();
    setUdpHeader(ethernetPacket);
    setSourcePort();
    setDestinationPort();
    setUdpChecksum();
    setPayload(ethernetPacket, packetLength);

    qDebug() << "■ Ethernet frame header: " << m_ethernetFrameHeader;
    std::cout <<"\n■ IPv4 header: " << convertToHex(getIpv4Header(), 1) << std::endl <<
                "\n■ IPv4 header checksum: " << getIpv4HeaderChecksum() << std::endl <<
                "\n■ Source IP Address: " << getSourceIPAdress() << std::endl <<
                "\n■ Destination IP Address: " << getDestinationIPAdress() << std::endl <<
                "\n■ UDP header: " << convertToHex(getUdpHeader(), 1) << std::endl <<
                "\n■ Source port: " << getSourcePort() << std::endl <<
                "\n■ Destination port: " << getDestinationPort() << std::endl;
    qDebug() << "\n■ UDP Checksum: " << getUdpChecksum();
    std::cout <<"\n■ UDP Payload: " << convertToHex(getPayload(), 1) << std::endl <<
                "\n■ UDP Payload size: " << getPayload().size() << std::endl <<
                "\n■ UDP Main Packet: " << convertToHex(getMainPacket(), 1) << std::endl <<
                "\n■ UDP Packet size: " << getMainPacket().size();
}

/*!
 * \brief Setter function for parsing the Ethernet Frame Header
 */
void UdpPackage::setEthernetFrameHeader(char* ethernetPacket, int packetLength)
{
    std::stringstream tempString;

    for (int i = 0; i < std::min(packetLength, ethernetFramelength); ++i) {
        tempString << ethernetPacket[i]; // Buffering the Ethernet Frame Header component
    }

    m_ethernetFrameHeader = QString::fromStdString(convertToHex(tempString.str(), 1));
}

/*!
 * \brief Getter function for parsing the Ethernet Frame Header
 * \return Ethernet Frame Header content - 20 byte
 */
QString UdpPackage::getEthernetFrameHeader() const
{
    return m_ethernetFrameHeader;
}

/*!
 * \brief Setter function for parsing the IPv4 Header
 */
void UdpPackage::setIpv4Header(char* ethernetPacket)
{
    std::stringstream tempString;

    for (int i = ethernetFramelength; i < (ethernetFramelength + ipv4HeaderLength); ++i) {
        tempString << ethernetPacket[i]; // Buffering IPv4 frame header component
    }

    m_ipv4Header = tempString.str();
}

/*!
 * \brief Getter function for parsing the IPv4 Header
 * \return IPv4 Header content - 14 byte
 */
std::string UdpPackage::getIpv4Header() const
{
    return m_ipv4Header;
}

/*!
 * \brief Setter function for parsing the IPv4 Header Checksum
 */
void UdpPackage::setIpv4HeaderChecksum()
{
    const auto ipv4HeaderChecksumTemp = convertToHex(m_ipv4Header.substr(4,2), 0);
    unsigned int ipv4HeaderChecksumDec = 0;

    std::stringstream ssIPHeaderChecksum;
    ssIPHeaderChecksum << std::hex << ipv4HeaderChecksumTemp;
    ssIPHeaderChecksum >> ipv4HeaderChecksumDec;

    m_ipv4HeaderChecksum = std::to_string(ipv4HeaderChecksumDec);
}

/*!
 * \brief Getter function for parsing the IP checksum from IPv4 Header
 * \return IPv4 header checksum content - 2 byte
 */
std::string UdpPackage::getIpv4HeaderChecksum() const
{
    return m_ipv4HeaderChecksum;
}

/*!
 * \brief Setter function for parsing the source IP Address
 */
void UdpPackage::setSourceIPAdress()
{
    const auto sourceIPAdressTemp = convertToHex(m_ipv4Header.substr(6,4), 0);

    std::stringstream ssnetworkID1Source;
    std::stringstream ssnetworkID2Source;
    std::stringstream ssnetworkID3Source;
    std::stringstream sshostIDSource;

    unsigned int networkID1DecSource = 0;
    unsigned int networkID2DecSource = 0;
    unsigned int networkID3DecSource = 0;
    unsigned int hostIDDecSource = 0;

    std::string networkIDComponent1 = sourceIPAdressTemp.substr(0,2);
    std::string networkIDComponent2 = sourceIPAdressTemp.substr(2,2);
    std::string networkIDComponent3 = sourceIPAdressTemp.substr(4,2);
    std::string hostIDComponent = sourceIPAdressTemp.substr(6,2);

    ssnetworkID1Source << std::hex << networkIDComponent1;
    ssnetworkID1Source >> networkID1DecSource;

    ssnetworkID2Source << std::hex << networkIDComponent2;
    ssnetworkID2Source >> networkID2DecSource;

    ssnetworkID3Source << std::hex << networkIDComponent3;
    ssnetworkID3Source >> networkID3DecSource;

    sshostIDSource << std::hex << hostIDComponent;
    sshostIDSource >> hostIDDecSource;

    m_sourceIPAdress = std::to_string(networkID1DecSource) + "." +
            std::to_string(networkID2DecSource) + "." +
            std::to_string(networkID3DecSource) + "." +
            std::to_string(hostIDDecSource);
}

/*!
 * \brief Getter function for parsing the Source IP Address
 * \return Source IP Address - 4 byte
 */
std::string UdpPackage::getSourceIPAdress() const
{
    return m_sourceIPAdress;
}

/*!
 * \brief Setter function for parsing the destination IP Address
 */
void UdpPackage::setDestinationIPAdress()
{
    const auto destinationIPAdressTemp = convertToHex(m_ipv4Header.substr(10,4), 0);

    std::stringstream ssnetworkID1Destination;
    std::stringstream ssnetworkID2Destination;
    std::stringstream ssnetworkID3Destination;
    std::stringstream sshostIDDestination;

    unsigned int networkID1DecDestination = 0;
    unsigned int networkID2DecDestination = 0;
    unsigned int networkID3DecDestination = 0;
    unsigned int hostIDecDestination = 0;

    std::string networkIDComponent1 = destinationIPAdressTemp.substr(0,2);
    std::string networkIDComponent2 = destinationIPAdressTemp.substr(2,2);
    std::string networkIDComponent3 = destinationIPAdressTemp.substr(4,2);
    std::string hostIDComponent = destinationIPAdressTemp.substr(6,2);

    ssnetworkID1Destination << std::hex << networkIDComponent1;
    ssnetworkID1Destination >> networkID1DecDestination;

    ssnetworkID2Destination << std::hex << networkIDComponent2;
    ssnetworkID2Destination >> networkID2DecDestination;

    ssnetworkID3Destination << std::hex << networkIDComponent3;
    ssnetworkID3Destination >> networkID3DecDestination;

    sshostIDDestination << std::hex << hostIDComponent;
    sshostIDDestination >> hostIDecDestination;

    m_destinationIPAdress = std::to_string(networkID1DecDestination) + "." +
            std::to_string(networkID2DecDestination) + "." +
            std::to_string(networkID3DecDestination) + "." +
            std::to_string(hostIDecDestination);
}

/*!
 * \brief Getter function for parsing the Destination IP Address
 * \return Destination IP Address - 4 byte
 */
std::string UdpPackage::getDestinationIPAdress() const
{
    return m_destinationIPAdress;
}

/*!
 * \brief Setter function for parsing the UDP Header
 */
void UdpPackage::setUdpHeader(char* ethernetPacket)
{
    std::stringstream tempString;

    for (int i = (ethernetFramelength + ipv4HeaderLength); i < (ethernetFramelength + ipv4HeaderLength + udpHeaderLength); ++i) {
        tempString << ethernetPacket[i]; // Buffering the UDP Header component
    }

    m_udpHeader = tempString.str();
}

/*!
 * \brief Getter function for parsing the UDP Header frame
 * \return UDP Header frame content  - 8 byte
 */
std::string UdpPackage::getUdpHeader() const
{
    return m_udpHeader;
}

/*!
 * \brief Setter function for parsing the source port
 */
void UdpPackage::setSourcePort()
{
    const auto sourcePortTemp = convertToHex(m_udpHeader.substr(0,2), 0);
    unsigned int sourcePortDec = 0;

    std::stringstream ssSourcePort;
    ssSourcePort << std::hex << sourcePortTemp;
    ssSourcePort >> sourcePortDec;

    m_sourcePort = std::to_string(sourcePortDec);
}

/*!
 * \brief Getter function for parsing the source port from UDP header
 * \return Source port content - 2 byte
 */
std::string UdpPackage::getSourcePort() const
{
    return m_sourcePort;
}

/*!
 * \brief Setter function for parsing the destination port
 */
void UdpPackage::setDestinationPort()
{
    const auto destinationPortTemp = convertToHex(m_udpHeader.substr(2,2), 0);
    unsigned int destinationPortDec = 0;

    std::stringstream ssDestinationPort;
    ssDestinationPort << std::hex << destinationPortTemp;
    ssDestinationPort >> destinationPortDec;

    m_destinationPort =  std::to_string(destinationPortDec);
}

/*!
 * \brief Getter function for parsing the destination port from UDP header
 * \return Destination port content - 2 byte
 */
std::string UdpPackage::getDestinationPort() const
{
    return m_destinationPort;
}

/*!
 * \brief Setter function for parsing the UDP Checksum
 */
void UdpPackage::setUdpChecksum()
{
    const auto udpChecksumTemp = convertToHex(m_udpHeader.substr(6,2), 0);
    unsigned int udpHeaderChecksumDec = 0;

    std::stringstream ssUDPHeaderChecksum;
    ssUDPHeaderChecksum << std::hex << udpChecksumTemp;
    ssUDPHeaderChecksum >> udpHeaderChecksumDec;

    m_udpChecksum = QString::number(udpHeaderChecksumDec);
}

/*!
 * \brief Getter function for parsing the UDP checksum from UDP header
 * \return UDP checksum content - 2 byte
 */
QString UdpPackage::getUdpChecksum() const
{
    return m_udpChecksum;
}

/*!
 * \brief Setter function for parsing the payload
 */
void UdpPackage::setPayload(char* ethernetPacket, int packetLength)
{
    std::stringstream tempString;

    for (int i = (ethernetFramelength + ipv4HeaderLength + udpHeaderLength); i < packetLength; ++i) {
        tempString << ethernetPacket[i]; // Buffering the UDP Header component
    }

    m_payload = tempString.str();
}

/*!
 * \brief Getter function for parsing the Payload
 * \return Payload content
 */
std::string UdpPackage::getPayload() const
{
    return m_payload;
}

/*!
 * \brief Setter function for parsing the whole package at once
 */
void UdpPackage::setMainPacket(char* ethernetPacket, int packetLength)
{
    std::stringstream tempString;

    for (int i = 0; i < packetLength; ++i) {
        tempString << ethernetPacket[i];

        m_mainPacket = tempString.str();
    }
}

/*!
 * \brief Getter function for parsing the whole UDP Packet
 * \return UDP Packet content
 */
std::string UdpPackage::getMainPacket() const
{
    return m_mainPacket;
}

/*!
 * \brief Getter function for parsing main the packet size
 */
void UdpPackage::setPacketLength(int packetLength)
{
    m_packetLength = packetLength;
}

/*!
 * \brief Getter function for parsing the packet length
 * \return Main packet size
 */
int UdpPackage::getPacketLength() const
{
    return m_packetLength;
}

/*!
 * \brief String to Hex conversion operation
 * \param frameData - relevant part of the packet to be used for conversion
 * \param spaceSelection - selection option up to user for printing out -> 0: no space, 1: space
 * \return To-hex-converted value of the relevant frame
 */
std::string UdpPackage::convertToHex(const std::string &frameData, bool spaceSelection) {

    std::stringstream streamer;

    streamer << std::hex << std::setfill('0') << std::uppercase;
    for (size_t i = 0; frameData.length() > i; ++i) {
        streamer << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(frameData[i])) << (spaceSelection ? " " : "");
    }

    return streamer.str();
}
