import QtQuick
import QtMultimedia
import com.refraction.PlayerController
import SongPlayer

Item {
    id: _root

    visible: PlayerController.currentSong

    Image {
        id: _albumImage

        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
        }
        width: 150
        height: 150

        source: PlayerController.currentSong?.imageSource ?? ''
    }

    Video {
        id: _albumVideo

        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
        }
        width: 150
        height: 150

        loops: MediaPlayer.Infinite
        volume: 0

        source: PlayerController.currentSong?.videoSource ?? ''
    }

    Text {
        id: _titleText

        anchors {
            left: _albumImage.right
            right: parent.right
            bottom: parent.verticalCenter
            margins: 20
        }

        color: 'white'
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        text: PlayerController.currentSong?.title ?? ''

        font {
            pixelSize: 20
            bold: true
        }
    }

    Text {
        id: _authorText

        anchors {
            top: parent.verticalCenter
            left: _titleText.left
            right: parent.right
            topMargin: 5
        }

        color: 'gray'
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        text: PlayerController.currentSong?.authorName ?? ''

        font.pixelSize: 16
    }

    onVisibleChanged: {
        if (visible) {
            _albumVideo.play()
        } else {
            _albumVideo.seek(0)
            _albumVideo.stop()
        }
    }
}
