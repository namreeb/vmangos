/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

 /*
  *
  * This code was written by namreeb (legal@namreeb.org) and is released with
  * permission as part of vmangos (https://github.com/vmangos/core)
  *
  */

#ifndef __WARDENSCANMGR_HPP_
#define __WARDENSCANMGR_HPP_

#include "WardenScan.hpp"
#include "Policies/Singleton.h"

#include <vector>
#include <memory>

class WardenScanMgr
{
    private:
        // these are stored as shared pointers to allow this collection to be emptied (presumably in the
        // process of repopulating it) without invalidating pointers held elsewhere, namely in the queues
        // of existing clients
        std::vector<std::shared_ptr<const Scan>> m_scans;

    public:
        // load static scans from database
        void LoadFromDB();

        size_t Count() const { return m_scans.size(); }

        void AddMacScan(const MacScan *);
        void AddMacScan(std::shared_ptr<MacScan>);

        void AddWindowsScan(const WindowsScan *);
        void AddWindowsScan(std::shared_ptr<WindowsScan>);

        std::vector<std::shared_ptr<const Scan>> GetRandomScans(ScanFlags flags, uint32 build) const;
};

#define sWardenScanMgr MaNGOS::Singleton<WardenScanMgr>::Instance()

#endif /*!__WARDENSCANMGR_HPP_*/