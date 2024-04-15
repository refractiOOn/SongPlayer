import QtQuick
import QtMultimedia
import com.refraction.PlayerController
import SongPlayer

Item {
    id: _root

    readonly property AudioInfo infoProvider: AudioInfo {}


    visible: PlayerController.currentSongIndex === infoProvider.songIndex

    Image {
        id: _albumImage

        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
        }
        width: 150
        height: 150

        source: infoProvider.imageSource
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

        source: infoProvider.videoSource
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
        text: infoProvider.title

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
        text: infoProvider.authorName

        font.pixelSize: 16
    }

    onVisibleChanged: {
        if (visible) {
            _albumVideo.play()
            PlayerController.changeAudioSource(infoProvider.audioSource)
        } else {
            _albumVideo.seek(0)
            _albumVideo.stop()
        }
    }

    Component.onCompleted: {
        if (PlayerController.currentSongIndex === infoProvider.songIndex) {
            PlayerController.changeAudioSource(infoProvider.audioSource)
        }
    }
}
