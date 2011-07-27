/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ4_RECORDING_H
#define _MUSICBRAINZ4_RECORDING_H

#include <string>
#include <iostream>

#include "musicbrainz4/GenericList.h"
#include "musicbrainz4/Entity.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CRecordingPrivate;

	class CArtistCredit;
	class CReleaseList;
	class CPUIDList;
	class CISRCList;
	class CRelationList;
	class CTagList;
	class CUserTagList;
	class CRating;
	class CUserRating;

	class CRecording: public CEntity
	{
	public:
		CRecording(const XMLNode& Node=XMLNode::emptyNode());
		CRecording(const CRecording& Other);
		CRecording& operator =(const CRecording& Other);
		virtual ~CRecording();

		virtual CRecording *Clone();

		std::string ID() const;
		std::string Title() const;
		int Length() const;
		std::string Disambiguation() const;
		CArtistCredit *ArtistCredit() const;
		CReleaseList *ReleaseList() const;
		CPUIDList *PUIDList() const;
		CISRCList *ISRCList() const;
		CRelationList *RelationList() const;
		CTagList *TagList() const;
		CUserTagList *UserTagList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;

		virtual std::string ElementName() const;

	protected:
		virtual bool ParseAttribute(const std::string& Name, const std::string& Value);
		virtual bool ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CRecordingPrivate * const m_d;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRecording& Recording);

#endif
