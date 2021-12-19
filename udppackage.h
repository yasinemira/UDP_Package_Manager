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
    Q_PROPERTY(QString ipv4Header READ getIpv4Header CONSTANT)
    Q_PROPERTY(QString ipv4HeaderChecksum READ getIpv4HeaderChecksum CONSTANT)
    Q_PROPERTY(QString sourceIPAdress READ getSourceIPAdress CONSTANT)
    Q_PROPERTY(QString destinationIPAdress READ getDestinationIPAdress CONSTANT)
    Q_PROPERTY(QString udpHeader READ getUdpHeader CONSTANT)
    Q_PROPERTY(QString sourcePort READ getSourcePort CONSTANT)    
    Q_PROPERTY(QString destinationPort READ getDestinationPort CONSTANT)
    Q_PROPERTY(QString payload READ getPayload CONSTANT)
    Q_PROPERTY(QString udpChecksum READ getUdpChecksum CONSTANT)
    Q_PROPERTY(int payloadLength READ getPayloadLength CONSTANT)
    Q_PROPERTY(int packetLength READ getPacketLength NOTIFY packetLengthChanged)

public:
    explicit UdpPackage(QObject *parent = nullptr);
    UdpPackage(char* ethernetPacket, int packetLength);
    ~UdpPackage();

    void setEthernetFrameHeader(char* ethernetPacket, int packetLength);
    void setIpv4Header(char* ethernetPacket);
    void setIpv4HeaderChecksum(char* ethernetPacket);
    void setSourceIPAdress(char* ethernetPacket);
    void setDestinationIPAdress(char *ethernetPacket);
    void setUdpHeader(char* ethernetPacket);
    void setSourcePort(char* ethernetPacket);
    void setDestinationPort(char* ethernetPacket);
    void setUdpChecksum(char* ethernetPacket);
    void setPayload(char* ethernetPacket, int packetLength);
    void setMainPacket(char* ethernetPacket, int packetLength);
    void setPayloadLength();
    void setPacketLength(int packetLength);

    void displayPackageDetails();

signals:
    void packetLengthChanged(int packetLength);

public slots:
    /**
     * Getter functions to log information neatly and in case the user
     * would like to see or use each component of the UDP packet individually
    **/
    QString getEthernetFrameHeader() const;
    QString getIpv4Header() const;
    QString getIpv4HeaderChecksum() const;
    QString getSourceIPAdress() const;
    QString getDestinationIPAdress() const;
    QString getUdpHeader() const;
    QString getSourcePort() const;
    QString getDestinationPort() const;
    QString getUdpChecksum() const;
    QString getPayload() const;
    QString getMainPacket() const;
    int getPayloadLength() const;
    int getPacketLength() const;

private:
    QString m_ethernetFrameHeader;
    QString m_ipv4Header;
    QString m_ipv4HeaderChecksum;
    QString m_sourceIPAdress;
    QString m_destinationIPAdress;
    QString m_udpHeader;
    QString m_sourcePort;
    QString m_destinationPort;
    QString m_udpChecksum;
    QString m_payload;
    QString m_mainPacket;
    int m_payloadLength;
    int m_packetLength;

    std::string convertToHex(const std::string& frameData, bool spaceSelection);
};

#endif // UDPPACKAGE_H
