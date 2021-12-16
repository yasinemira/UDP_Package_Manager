#ifndef UDPPACKAGE_H
#define UDPPACKAGE_H

#include <QObject>

class UdpPackage : public QObject
{
    Q_OBJECT

    /***A classical UDP Data Packet via Ethernet can be illustrated as below

                                                      <-------------------UDP Datagram-------...........>
        ______________________________________________________________________________________________....
       |                        |                     |             |
       | Ethernet Frame Header  |     IPv4 Header     | UDP Header  |       Payload                   ~~~
       |                        |                     |             |
       |________________________|_____________________|_____________|_________________________________....
       <--------20 bytes-------><------ 14-bytes-----><---8-bytes---><--------- n-bytes-----...........>
                                                        |
                                                        |--> 2-bytes source-port IP
                                                        |--> 2-bytes destination-port IP
                                                        |--> 2-bytes header length
                                                        |--> 2-bytes header checksum

***/

    Q_PROPERTY(QString ethernetFrameHeader READ getEthernetFrameHeader CONSTANT)
    Q_PROPERTY(QString payload READ getPayload CONSTANT)
    Q_PROPERTY(QString udpChecksum READ getUdpChecksum CONSTANT)
    //Q_PROPERTY(int payload READ getPayloadLength CONSTANT)
    Q_PROPERTY(int packetLength READ getPacketLength NOTIFY packetLengthChanged)

public:
    explicit UdpPackage(QObject *parent = nullptr);
    UdpPackage(char* ethernetPacket, int packetLength);
    ~UdpPackage();

    void setEthernetFrameHeader(char* ethernetPacket, int packetLength);
    void setIpv4Header(char* ethernetPacket);
    void setIpv4HeaderChecksum();
    void setSourceIPAdress();
    void setDestinationIPAdress();
    void setUdpHeader(char* ethernetPacket);
    void setSourcePort();
    void setDestinationPort();
    void setUdpChecksum();
    void setPayload(char* ethernetPacket, int packetLength);
    void setMainPacket(char* ethernetPacket, int packetLength);
    //void setPayloadLength();
    void setPacketLength(int packetLength);

    void displayPackageDetails(char* ethernetPacket, int packetLength);

signals:
    void packetLengthChanged(int packetLength);

public slots:
    /**
     * Getter functions to log information neatly and in case the user
     * would like to see or use each component of the UDP packet individually
    **/
    QString getEthernetFrameHeader() const;
    std::string getIpv4Header() const;
    std::string getIpv4HeaderChecksum() const;
    std::string getSourceIPAdress() const;
    std::string getDestinationIPAdress () const;
    std::string getUdpHeader() const;
    std::string getSourcePort() const;
    std::string getDestinationPort() const;
    QString getUdpChecksum() const;
    QString getPayload() const;
    std::string getMainPacket() const;
    //int getPayloadLength() const;
    int getPacketLength() const;

private:
    QString m_ethernetFrameHeader;
    std::string m_ipv4Header;
    std::string m_ipv4HeaderChecksum;
    std::string m_sourceIPAdress;
    std::string m_destinationIPAdress;
    std::string m_udpHeader;
    std::string m_sourcePort;
    std::string m_destinationPort;
    QString m_udpChecksum;
    QString m_payload;
    std::string m_mainPacket;
    int m_payloadLength;
    int m_packetLength;

    std::string convertToHex(const std::string& frameData, bool spaceSelection);
};

#endif // UDPPACKAGE_H
