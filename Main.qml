import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls.Imagine
import QtQuick.Dialogs
import QtQuick.Effects
import Qt5Compat.GraphicalEffects
import Widgets
import Models
import Enums
import Theme

Window {
    width: 400
    height: 580
    visible: true
    title: qsTr("Color Extractor")

//    ScrollView{
//        anchors.top: parent.top
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.bottom: parent.bottom
//        contentWidth: layout.width
//        contentHeight: layout.height

//        ColumnLayout{
//            id: layout

//            Item{
//                id: _imageWrapper
//                Layout.minimumWidth: 200
//                Layout.maximumWidth: 200
//                Layout.minimumHeight: _image.height
//                Layout.maximumHeight: _image.height
//                Image{
//                    id: _image
//                    width: parent.width
//                    fillMode: Image.PreserveAspectFit

//                    onSourceChanged: {
//                        _cropper.x1 = 0
//                        _cropper.y1 = 0
//                        _cropper.x2 = _cropper.width
//                        _cropper.y2 = _cropper.height
//                    }
//                }
//                Cropper{
//                    id: _cropper
//                    width: _image.width
//                    height: _image.height
//                    opacity: 0

//                    MouseArea{
//                        anchors.fill: parent
//                        cursorShape: Qt.PointingHandCursor
//                        preventStealing: true
//                        onPressed: {
//                            _cropper.opacity = 1
//                            _cropper.x1 = mouseX
//                            _cropper.y1 = mouseY
//                        }

//                        onMouseXChanged: {
//                            _cropper.x2 = mouseX
//                        }
//                        onMouseYChanged: {
//                            _cropper.y2 = mouseY
//                        }
//                    }
//                }
//            }



//            Flow{
//               id: _flow
//               Layout.minimumWidth: 400
//               Layout.maximumWidth: 400
//                spacing: 10

//                Repeater{
//                    model: _colorExtractorModel
//                    delegate: Rectangle{
//                        width: 40;height: 40
//                        radius: 5
//                        color: model.Color
//                    }
//                }
//            }




//            RowLayout{
//                Button{
//                    id: _button1
//                    text: "Select Image"
//                    onClicked: {
//                        _fileDialog.open()
//                    }
//                }
//                Button{
//                    id: _button2
//                    text: "Start Color Extraction"
//                    onClicked: {
//                        _colorExtractorModel.startColorExtraction(_image.source,_image.width,Qt.point(_cropper.x1,_cropper.y1),Qt.point(_cropper.x2,_cropper.y2))
//                        _button2.enabled = false
//                    }
//                }
//            }
//        }


//    }


//    Item{
//        id: _menu1
//        anchors.top: parent.top
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.topMargin: 10
//        width: _menu1Layout.width
//        height: _menu1Layout.height

//        RowLayout{
//            id: _menu1Layout

//            Rectangle{
//                id: _vCenter
//                Layout.minimumWidth: 35
//                Layout.minimumHeight: width
//                radius: width/2
//                color: "lightsteelblue"

//                MouseArea{
//                    anchors.fill: parent
//                    cursorShape: Qt.PointingHandCursor
//                    onClicked: {
//                        _colorExtractorModel.changeAlgorithm(AlgorithmType.HCenter)
//                    }
//                }
//            }
//        }
//    }



    //HEADER
    Item{
        id: _header
        anchors.left: parent.left
        anchors.right: parent.right
        height: 60
        Rectangle{
            anchors.fill: parent
            color: AppTheme.primaryColor

            Text{
                anchors.centerIn: parent
                text: "Image Color Extractor"
                font.pixelSize: 15
                color: AppTheme.accentColor
            }
        }
    }

    Image{
        id: _image
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        fillMode: Image.PreserveAspectFit
    }

    Cropper{
        id: _cropper
        x: _image.x
        y: _image.y
        width: _image.width
        height: _image.height
        opacity: 0

        MouseArea{
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onPressed:{
                _cropper.opacity = 1
                _cropper.x1 = mouseX
                _cropper.y1 = mouseY
            }
            onMouseXChanged: {
                _cropper.x2 = mouseX
            }
            onMouseYChanged: {
                _cropper.y2 = mouseY
            }
        }


    }

    //BUTTONS
    RowLayout{
        id: _buttonsLayout
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Rectangle{
            Layout.fillWidth: true
            Layout.minimumHeight: 50
            color: AppTheme.accentColor

            Text{
                anchors.centerIn: parent
                text: "Choose Image"
                color: "white"
            }

            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    _fileDialog.open()
                }
            }
        }
        Rectangle{
            id: _exctrationButton
            Layout.fillWidth: true
            Layout.minimumHeight: 50
            color: AppTheme.accentColor

            Text{
                anchors.centerIn: parent
                text: "Extract Colors"
                color: "white"
            }

            MouseArea{
                id: _exctrationButtonMouseArea
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    _colorExtractorModel.startColorExtraction(_image.source,_image.width,Qt.point(_cropper.x1,_cropper.y1),Qt.point(_cropper.x2,_cropper.y2))
                    _exctrationButtonMouseArea.enabled = false
                }
            }
        }
    }

    //MENU

    Item{
        id: _menuFloatingButton
        width: 50
        height: width
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.bottomMargin: 60

        state: "inactive"
        states: [
            State {
                name: "active"
                PropertyChanges {
                    target:  _menuButtonBackground
                    rotation: 180

                }
            },
            State{
                name: "inactive"
                PropertyChanges{
                    target:  _menuButtonBackground
                    rotation: 0
                }
            }

        ]


        function toggleState(){
            if(state ==="inactive"){
                state = "active"
                _appMenu.open()
            }

            else{
                 state = "inactive"
                _appMenu.close()
            }

        }

        Rectangle{
            id: _menuButtonBackground
            anchors.fill: parent
            radius: width/2
            layer.enabled: true
            color: AppTheme.accentColor
            layer.effect: MultiEffect{
                shadowEnabled:true
                shadowColor: "#cccccc"
                shadowHorizontalOffset: 0
                shadowVerticalOffset: 0
                shadowBlur: 0.5
            }

            Behavior on rotation{
                NumberAnimation{duration: 200}
            }

            Image{
                id: _menuIcon
                anchors.centerIn: parent
                sourceSize.width: 20
                sourceSize.height: 20
                source: "qrc:/icons/widgets.svg"
                opacity: 0
            }
            ColorOverlay{
                anchors.fill: _menuIcon
                source: _menuIcon
                color: Theme.primaryColor
            }
        }

        MouseArea{
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor

            onClicked: {
                _menuFloatingButton.toggleState()
            }
        }
    }


    AppMenu{
        id: _appMenu
        anchors.bottom: _menuFloatingButton.top
        anchors.right: _menuFloatingButton.right
        anchors.bottomMargin: 15
    }





    ColorExtractorModel{
        id: _colorExtractorModel
    }

    FileDialog{
        id: _fileDialog

        onAccepted:{
           _image.source = currentFile
        }
    }


    Connections{
        target: _colorExtractorModel
        ignoreUnknownSignals: true


        function onColorExtractionFinished(){
            //_button2.enabled = true
        }
    }

    Connections{
        target: _appMenu
        ignoreUnknownSignals: true

        function onAlgorithmChanged(algorithm){
            _colorExtractorModel.changeAlgorithm(algorithm)
        }
    }



}
