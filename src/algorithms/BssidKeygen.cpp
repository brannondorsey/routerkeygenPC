/*
 * Copyright 2016 Alex Stanev <alex@stanev.org>
 *
 * This file is part of Router Keygen.
 *
 * Router Keygen is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Router Keygen is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Router Keygen.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "BssidKeygen.h"

BssidKeygen::BssidKeygen(QString ssid, QString mac, int flags, int offset) :
		Keygen(ssid, mac) {
    kgname = "Bssid";
    this->flags = flags;
    this->offset = offset;
}

QVector<QString> & BssidKeygen::getKeys() {
    QString mac = getMacAddress();
    if ( mac.length() != 12 )
        throw ERROR;

    /* Apply offset value */
    if (offset != 0) {
        QString shortMac = mac.left(10);
        int last = mac.right(2).toInt(0, 16);
        mac = shortMac + QString("%1").arg(last + offset, 2, 16, QLatin1Char('0')).right(2);
    }
    
    /* Check flags */
    if (flags & FlagLen8) {
        if (flags & FlagUc)
            results.append(mac.right(8).toUpper());
        if (flags & FlagLc)
            results.append(mac.right(8).toLower());
    }
    if (flags & FlagLen10) {
        if (flags & FlagUc)
            results.append(mac.right(10).toUpper());
        if (flags & FlagLc)
            results.append(mac.right(10).toLower());
    }
    if (flags & FlagLen12) {
        if (flags & FlagUc)
            results.append(mac.toUpper());
        if (flags & FlagLc)
            results.append(mac.toLower());
    }

    if (results.isEmpty())
        throw ERROR;

    return results;
}
