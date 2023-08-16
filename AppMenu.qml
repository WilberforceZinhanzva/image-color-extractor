import QtQuick
import QtQuick.Effects
import QtQuick.Layouts
import Theme
import Enums

Item {
    id: root

    implicitWidth: 50
    implicitHeight: _background.height
    visible: false

    signal algorithmChanged(int algorithm)


    function open(){
        root.visible = true
        _openAnimation.start()
    }
    function close(){
        _closeAnimation.start()

    }

    ParallelAnimation{
        id: _openAnimation

        NumberAnimation{
            target: _background
            properties: "y"
            from: _columnLayout.height + 20
            to: 0
            duration: 200
        }

        NumberAnimation{
            target: _background
            properties: "height"
            from: 0
            to: _columnLayout.height + 20
            duration: 200
        }

        NumberAnimation{
            target: root
            properties: "opacity"
            from: 0
            to: 1
            duration: 100
        }
    }

    SequentialAnimation{
        id: _closeAnimation


        ParallelAnimation{

            NumberAnimation{
                target: _background
                properties: "y"
                from: 0
                to: _columnLayout.height + 20
                duration: 200
            }

            NumberAnimation{
                target: _background
                properties: "height"
                from: _columnLayout.height + 20
                to: 0
                duration: 200
            }

            NumberAnimation{
                target: root
                properties: "opacity"
                from: 1
                to: 0
                duration: 200
            }

        }

        ScriptAction{
            script: root.visible = false
        }
    }

    Rectangle{
        id: _background
        width: parent.width
        height: _columnLayout.height
        radius: width/2
        color: "transparent"


        ColumnLayout{
            id: _columnLayout
            anchors.centerIn: parent
            spacing: 10

            AlgoButton{
                id: _vCenterAlgorithmButton
                icon: "qrc:/icons/vertical.svg"
                selected: true
                onClicked: {
                    root.algorithmChanged(AlgorithmType.VCenter)
                    _topLeftDiagonalAlgorithmButton.selected = false
                    _topRightDiagonalAlgorithmButton.selected = false
                    _hCenterAlgorithmButton.selected = false
                }
            }
            AlgoButton{
                id: _topLeftDiagonalAlgorithmButton
                icon: "qrc:/icons/diagonal.svg"
                onClicked: {
                    root.algorithmChanged(AlgorithmType.LeftDiagonal)
                    _vCenterAlgorithmButton.selected=false
                    _topRightDiagonalAlgorithmButton.selected = false
                    _hCenterAlgorithmButton.selected = false
                }
            }
            AlgoButton{
                id: _topRightDiagonalAlgorithmButton
                icon: "qrc:/icons/diagonal.svg"
                flipped: true
                onClicked: {
                    root.algorithmChanged(AlgorithmType.RightDiagonal)
                    _vCenterAlgorithmButton.selected=false
                    _topLeftDiagonalAlgorithmButton.selected = false
                    _hCenterAlgorithmButton.selected = false
                }
            }
            AlgoButton{
                id: _hCenterAlgorithmButton
                icon: "qrc:/icons/horizontal.svg"
                onClicked: {
                    root.algorithmChanged(AlgorithmType.HCenter)
                    _vCenterAlgorithmButton.selected=false
                    _topLeftDiagonalAlgorithmButton.selected = false
                    _topRightDiagonalAlgorithmButton.selected = false
                }
            }
        }

    }

}
