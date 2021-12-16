import QtQuick 2.0

/***
    \brief: A generic Rectangle component class to avoid content repetition for each instance
***/

Rectangle {
    id: root
    property string componentDetail

    QtObject {
        id: internal
        readonly property int rectWidth: 250
        readonly property int rectHeight: 50
        readonly property int rightMarginRect: 80
    }

    anchors.right: parent.right
    anchors.rightMargin: internal.rightMarginRect
    width: internal.rectWidth
    height: internal.rectHeight
    color: "#ffffff"
    radius: 20

    Text {
        id: udpPackageDetail
        anchors.fill: parent
        anchors.centerIn: parent
        text: root.componentDetail
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
        font.family: "Helvetica"
    }
}
