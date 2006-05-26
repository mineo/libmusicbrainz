/*
 * MusicBrainz -- The Internet music metadatabase
 *
 * Copyright (C) 2006 Lukas Lalinsky
 *	
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA	 02111-1307	 USA
 */
 
#ifndef __MUSICBRAINZ3_ENTITY_H__
#define __MUSICBRAINZ3_ENTITY_H__

#include <string>
#include <musicbrainz3/musicbrainz.h> 
#include <musicbrainz3/lists.h> 
#include <musicbrainz3/relation.h> 

namespace MusicBrainz
{

	/**
	 * A first-level MusicBrainz class.
	 *
	 * All entities in MusicBrainz have unique IDs (which are absolute URIs)
	 * and may have any number of relations (Relation) to other entities.
	 * This class is abstract and should not be instantiated.
	 * 
	 * Relations are differentiated by their \e target \e type, that means,
	 * where they link to. MusicBrainz currently supports four target types
	 * (artists, releases, tracks, and URLs) each identified using a URI.
	 * To get all relations with a specific target type, you can use
	 * getRelations and pass one of the following constants as the
	 * parameter:
	 *
	 *	 - Relation::TO_ARTIST
	 *	 - Relation::TO_RELEASE
	 *	 - Relation::TO_TRACK
	 *	 - Relation::TO_URL
	 *	   
	 * @see Relation 
	 */
	class MB_API Entity
	{
	protected:
	
		/**
		 * Constructor.
		 *
		 * This should only used by derived classes.
		 *
		 * @param id a string containing an absolute URI 
		 */	 
		Entity(const std::string &id);
		
	public:
		
		virtual ~Entity();
		
		/**
		 * Returns a MusicBrainz ID.
		 * 
		 * @return a string containing a URI
		 */
		virtual std::string getId() const;
		
		/**
		 * Sets a MusicBrainz ID.
		 *
		 * @param value a string containing an absolute URI	 
		 */
		virtual void setId(const std::string &value);

		// TODO, FIXME, ... :)	
		const RelationList &getRelations() const;
		
		/**
		 * Adds a relation.
		 *
		 * This method adds \a relation to the list of relations. The
		 * given relation has to be initialized, at least the target
		 * type has to be set.
		 *
		 * @param relation a pointer to Relation object to add
		 */
		void addRelation(Relation *relation);
		
	private:
	
		std::string id;
		RelationList relations;
		
	};
	
}

#endif