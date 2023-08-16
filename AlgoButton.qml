import QtQuick
import QtQuick.Effects
import Qt5Compat.GraphicalEffects
import Theme


Item {
    id: root
    implicitHeight: 40
    implicitWidth: 40

    property color backgroundColor: AppTheme.primaryColor
    property color foregroundColor: AppTheme.accentColor
    property string icon
    property bool flipped: false
    property bool selected: false


    signal clicked()

    Rectangle{
        anchors.fill: parent
        radius: width/2
        color: root.selected ? root.foregroundColor : root.backgroundColor
        layer.enabled: true
        layer.effect: MultiEffect{
            shadowEnabled: true
            shadowColor: "#cccccc"
            shadowBlur: 0.8
            shadowHorizontalOffset: 0
            shadowVerticalOffset: 0
        }

        Item{
            anchors.centerIn: parent
            width: 20
            height: width

            Image{
                id: _icon
                sourceSize.width: parent.width
                sourceSize.height: parent.height
                source: root.icon
                rotation: root.flipped ? 90 : 0
            }
            ColorOverlay{
                anchors.fill: _icon
                source: _icon
                color: root.selected? root.backgroundColor : root.foregroundColor
                rotation: root.flipped ? 90 : 0
            }

        }
    }


    MouseArea{
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            root.selected = true
            root.clicked()

        }
    }

}
