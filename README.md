# eyeball
**Bringing an obsolete web-cam back to life**

## Introduction
The DCS-930L camera from 2010 is no longer supported by web browsers because they have dropped support for ActiveX and java NPAPI.

However, the camera still supports FTP, so it can push images onto a file system while the *eyeball* application displays them as they arrive.

## RAM Disk
In order to save wear and tear on the hard disk, a RAM Disk is set up and mounted and that is the target of the FTP.  Images will typically arrive at a rate of 3 per second, but there is a less reliable mode where up to 12 frames are sent per second.

To mount the RAM Disk file system:
* `sudo mkdir /mnt/ramdisk/Pictures`
* `sudo mount -t tmpfs -o size=4m tmpfs /mnt/ramdisk`

## Setting up Camera
The Camera FTP settings:
* *Host Name* is just the URL of the Host Computer running *eyeball*
* *Port* must be 21
* *User Name* is the account name on the Host Computer
* *Password* is the password on the Host Computer
* *Path* must be `/mnt/ramdisk/Pictures`
* *Passive Mode* can be used to bypass firewall problems

Hit the *Save Settings* button.

At this point the FTP can be tested with the *Test* button.
After the test, go to Status to see if the test passed.
The test will send a test JPG image to `/mnt/ramdisk/Pictures`

If the test passed, then a stream of continuous pictures can be schedules by setting up the *Time Schedule* settings:
* Check `Enable uploading images to the FTP server`
* Check `Always` or any other schedule preference
* *image Frequency* should be 3 Frames Per Second, but any other preference is supported.
* *Base File Name* should be `DCS-930L`
* *File* should be set to `Sequence Number Suffix Up to 4`

Hit the *Save Settings* button again and the FTP process will begin.
To shut off the FTP:
* Uncheck the `Enable uploading images to FTP server`
* Hit the *Save Settings* button.

## FTP Stream
When the FTP is running, it sends a series of JPG images to the ramdisk, overwriting one of the following four files each time:
* DCS-930L1.JPG
* DCS-930L2.JPG
* DCS-930L3.JPG
* DCS-930L4.JPG

## eyeball
Eyeball is a Qt program, so run `qmake eyeball.pro` to generate the Makefile, then run `make`.

Run the eyeball app by typing `./eyeball`
The app is notified when any of the files are changed and will always render the last completed image.

## high rate
The application is very reliable at frame rates of 3Hz or less.
When the Auto Image Frequency is selected on the camera, the frame rate will rise to around 10 frames per second.  The application can handle this frame rate but there are periods of time where the FTP process shuts down for anywhere from 3 seconds to 20 seconds.

The process seems to always heal itself and recover.

The high rate uses way more bandwidth than 3 frames per second and does not provide any added security.
