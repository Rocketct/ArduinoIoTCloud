/*
 * This file is part of ArduinoIoTCloud.
 *
 * Copyright 2019 ARDUINO SA (http://www.arduino.cc/)
 *
 * This software is released under the GNU General Public License version 3,
 * which covers the main part of arduino-cli.
 * The terms of this license can be found at:
 * https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * You can be released from the requirements of the above licenses by purchasing
 * a commercial license. Buying such a license is mandatory if you want to modify or
 * otherwise use the software for commercial activities involving the Arduino
 * software without disclosing the source code of your own applications. To purchase
 * a commercial license, send an email to license@arduino.cc.
 */

/******************************************************************************
 * INCLUDE
 ******************************************************************************/

#include "ConnectionManager.h"

#include <Ethernet.h>
#define BOARD_HAS_ETHERNET

/******************************************************************************
 * CLASS DECLARATION
 ******************************************************************************/

class EthConnectionManager : public ConnectionManager {
public:
  EthConnectionManager(uint8_t * mac, int const ss_pin = -1);

  virtual void init();
  virtual unsigned long getTime();
  virtual void check();
  virtual Client &getClient() { return ethClient; };
  virtual UDP &getUDP() { return udp; };

private:

  void changeConnectionState(NetworkConnectionState _newState);
  
  const int CHECK_INTERVAL_IDLE = 100;
  const int CHECK_INTERVAL_INIT = 100;
  const int CHECK_INTERVAL_CONNECTING = 500;
  const int CHECK_INTERVAL_GETTIME = 100;
  const int CHECK_INTERVAL_CONNECTED = 10000;
  const int CHECK_INTERVAL_RETRYING = 5000;
  const int CHECK_INTERVAL_DISCONNECTED = 1000;
  const int CHECK_INTERVAL_ERROR = 500;

  unsigned long lastConnectionTickTime, lastNetworkStep;
  uint8_t* mac;
  int ss_pin;
  EthernetClient ethClient;
  EthernetUDP udp;
  int connectionTickTimeInterval;
};
