# edge-client

Refactor of older client. Trying to improve: 
- structure of the project
- simplicity
- readability

## building

```shell
git clone git@github.com:bobolle/edge.git
cd edge

cmake -B build -DWIFI_SSID="yourssid" -DWIFI_PASSWD="ssidpassword"
make -C build

# mount the .uf2 file to device
```
