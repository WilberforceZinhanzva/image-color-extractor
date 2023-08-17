import QtQuick
import QtQuick.Controls.Imagine
import QtQuick.Effects

Item {
    id: root
    visible: false

    property alias colorsModel : _repeater.model

    Rectangle{
        id: _background

        anchors.fill: parent
        color: Qt.rgba(0,0,0,0.8)


        ScrollView{
            id: _scrollview
            anchors.fill: parent
            contentHeight: _flow.height
            contentWidth: _flow.width


            Flow{
                id: _flow
                width: _background.width
                spacing: 10
                leftPadding: 20
                topPadding: 20
                bottomPadding: 20


                Repeater{
                    id: _repeater
                    delegate: Item{
                        width: 60
                        height: width

                        Rectangle{
                            id: _colorRec
                            anchors.fill: parent
                            color: model.Color
                            radius: 5
                            layer.enabled: true
                            layer.effect: MultiEffect{
                                shadowEnabled: true
                                shadowColor: "white"
                                shadowBlur: 0.3
                                shadowVerticalOffset: 0
                                shadowHorizontalOffset: 0
                            }

                            Text{
                                anchors.centerIn: parent
                                text: _colorRec.color.toString()
                                color: "black"
                                layer.enabled: true
                                layer.effect: MultiEffect{
                                    shadowEnabled: true
                                    shadowColor: "white"
                                    shadowBlur: 0.3
                                    shadowVerticalOffset: 0
                                    shadowHorizontalOffset: 0
                                }
                            }

                        }
                    }

                }

            }
        }
    }

    MouseArea{
        anchors.fill: parent
        onClicked: root.visible = false
    }

}
