#include "musicbrainz4/mb_c.h"

#include <string.h>

#include "musicbrainz4/Alias.h"
#include "musicbrainz4/Annotation.h"
#include "musicbrainz4/Artist.h"
#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/Attribute.h"
#include "musicbrainz4/CDStub.h"
#include "musicbrainz4/Collection.h"
#include "musicbrainz4/Disc.h"
#include "musicbrainz4/FreeDBDisc.h"
#include "musicbrainz4/ISRC.h"
#include "musicbrainz4/Label.h"
#include "musicbrainz4/LabelInfo.h"
#include "musicbrainz4/Medium.h"
#include "musicbrainz4/Metadata.h"
#include "musicbrainz4/NameCredit.h"
#include "musicbrainz4/NoneMBTrack.h"
#include "musicbrainz4/Query.h"
#include "musicbrainz4/Recording.h"
#include "musicbrainz4/Relation.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/Tag.h"
#include "musicbrainz4/UserTag.h"
#include "musicbrainz4/Work.h"

template <class T>
int GetListSize(void *List)
{
	int Ret=0;

	if (List)
	{
		MusicBrainz4::CGenericList<T> *TheList=reinterpret_cast<MusicBrainz4::CGenericList<T> *>(List);
		Ret=TheList->Items().size();
	}

	return Ret;
}

template <class T>
T *GetListItem(void *List, int Item)
{
	T *Ret=0;

	if (List)
	{
		MusicBrainz4::CGenericList<T> *TheList=reinterpret_cast<MusicBrainz4::CGenericList<T> *>(List);
		if (Item<(int)TheList->Items().size())
		{
			std::list<T> Items=TheList->Items();
			typename std::list<T>::const_iterator ThisItem=Items.begin();

			int count=0;

			while (count<Item)
			{
				++count;
				++ThisItem;
			}

			Ret=new T(*ThisItem);
		}
	}

	return Ret;
}

#define MB4_C_NEW_NOARGS(TYPE1, TYPE2) \
	Mb4##TYPE1 \
	mb4_##TYPE2##_new() \
	{ \
		TYPE1 *o = new TYPE1(); \
		return (Mb4##TYPE1)o; \
	}

#define MB4_C_DELETE(TYPE1, TYPE2) \
	void \
	mb4_##TYPE2##_delete(Mb4##TYPE1 o) \
	{ \
		delete (MusicBrainz4::C##TYPE1 *)o; \
	}

#define MB4_C_STR_SETTER(TYPE1, TYPE2, PROP1, PROP2) \
	void \
	mb4_##TYPE2##_set_##PROP2(Mb4##TYPE1 o, const char *str) \
	{ \
		try { \
			((TYPE1 *)o)->Set##PROP1(str); \
		} \
		catch (...) { \
		} \
	}

#define MB4_C_INT_SETTER(TYPE1, TYPE2, PROP1, PROP2) \
	void \
	mb4_##TYPE2##_set_##PROP2(Mb4##TYPE1 o, int i) \
	{ \
		try { \
			((TYPE1 *)o)->Set##PROP1(i); \
		} \
		catch (...) { \
		} \
	}

#define MB4_C_STR_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	void \
	mb4_##TYPE2##_get_##PROP2(Mb4##TYPE1 o, char *str, int len) \
	{ \
		try { \
			strncpy(str, ((MusicBrainz4::C##TYPE1 *)o)->PROP1().c_str(), len); \
			str[len-1]='\0'; \
		} \
		catch (...) { \
			str[0] = '\0'; \
		} \
	}

#define MB4_C_INT_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	int \
	mb4_##TYPE2##_get_##PROP2(Mb4##TYPE1 o) \
	{ \
		try { \
			return ((TYPE1 *)o)->get##PROP1(); \
		} \
		catch (...) { \
			return 0; \
		} \
	}

#define MB4_C_BOOL_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	int \
	mb4_##TYPE2##_get_##PROP2(Mb##TYPE1 o) \
	{ \
		try { \
			return ((TYPE1 *)o)->PROP1() ? 1 : 0; \
		} \
		catch (...) { \
			return 0; \
		} \
	}

#define MB4_C_OBJ_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	Mb4##PROP1 \
	mb4_##TYPE2##_get_##PROP2(Mb4##TYPE1 o) \
	{ \
		try { \
			return (Mb4##PROP1)((MusicBrainz4::C##TYPE1 *)o)->PROP1(); \
		} \
		catch (...) { \
			return (Mb4##PROP1)0; \
		} \
	}

#define MB4_C_LIST_GETTER(TYPE1, TYPE2) \
	int \
	mb4_##TYPE2##_list_size(Mb4##TYPE1##List List) \
	{ \
		try { \
			return GetListSize<MusicBrainz4::C##TYPE1>(List); \
		} \
		catch (...) { \
			return 0; \
		} \
	} \
 \
	Mb4##TYPE1 \
	mb4_##TYPE2##_list_item(Mb4##TYPE1##List List, int Item) \
	{ \
		try { \
			return GetListItem<MusicBrainz4::C##TYPE1>(List,Item); \
		} \
		catch (...) { \
			return (Mb4##TYPE1)0; \
		} \
	}

MB4_C_DELETE(Alias,alias)
MB4_C_STR_GETTER(Alias,alias,Type,type)
MB4_C_STR_GETTER(Alias,alias,Script,script)
MB4_C_STR_GETTER(Alias,alias,Text,text)

MB4_C_DELETE(Annotation,annotation)
MB4_C_STR_GETTER(Annotation,annotation,Type,type)
MB4_C_STR_GETTER(Annotation,annotation,Entity,entity)
MB4_C_STR_GETTER(Annotation,annotation,Name,name)
MB4_C_STR_GETTER(Annotation,annotation,Text,text)

MB4_C_DELETE(Artist,artist)
MB4_C_STR_GETTER(Artist,artist,ID,id)
MB4_C_STR_GETTER(Artist,artist,Type,type)
MB4_C_STR_GETTER(Artist,artist,Name,name)
MB4_C_STR_GETTER(Artist,artist,SortName,sortname)
MB4_C_STR_GETTER(Artist,artist,Gender,gender)
MB4_C_STR_GETTER(Artist,artist,Country,country)
MB4_C_STR_GETTER(Artist,artist,Disambiguation,disambiguation)
MB4_C_OBJ_GETTER(Artist,artist,Lifespan,lifespan)
MB4_C_OBJ_GETTER(Artist,artist,AliasList,aliaslist)
MB4_C_OBJ_GETTER(Artist,artist,RecordingList,recordinglist)
MB4_C_OBJ_GETTER(Artist,artist,ReleaseList,releaselist)
MB4_C_OBJ_GETTER(Artist,artist,ReleaseGroupList,releasegrouplist)
MB4_C_OBJ_GETTER(Artist,artist,LabelList,labellist)
MB4_C_OBJ_GETTER(Artist,artist,WorkList,worklist)
MB4_C_OBJ_GETTER(Artist,artist,RelationList,relationlist)
MB4_C_OBJ_GETTER(Artist,artist,TagList,taglist)
MB4_C_OBJ_GETTER(Artist,artist,UserTagList,usertaglist)
MB4_C_OBJ_GETTER(Artist,artist,Rating,rating)
MB4_C_OBJ_GETTER(Artist,artist,UserRating,userrating)

MB4_C_DELETE(ArtistCredit,artistcredit)
MB4_C_OBJ_GETTER(ArtistCredit,artistcredit,NameCreditList,namecreditlist)

MB4_C_DELETE(Attribute,attribute)
MB4_C_STR_GETTER(Attribute,attribute,Text,text)

MB4_C_DELETE(CDStub,cdstub)
MB4_C_STR_GETTER(CDStub,cdstub,ID,id)
MB4_C_STR_GETTER(CDStub,cdstub,Title,title)
MB4_C_STR_GETTER(CDStub,cdstub,Artist,artist)
MB4_C_STR_GETTER(CDStub,cdstub,Barcode,barcode)
MB4_C_STR_GETTER(CDStub,cdstub,Comment,comment)
MB4_C_OBJ_GETTER(CDStub,cdstub,NoneMBTrackList,NoneMBTrackList)

MB4_C_DELETE(Collection,collection)
MB4_C_STR_GETTER(Collection,collection,ID,id)
MB4_C_STR_GETTER(Collection,collection,Name,name)
MB4_C_STR_GETTER(Collection,collection,Editor,editor)
MB4_C_OBJ_GETTER(Collection,collection,ReleaseList,releaselist)

MB4_C_DELETE(Disc,disc)
MB4_C_STR_GETTER(Disc,disc,ID,id)
MB4_C_STR_GETTER(Disc,disc,Sectors,sectors)
MB4_C_OBJ_GETTER(Disc,disc,ReleaseList,releaselist)

MB4_C_DELETE(FreeDBDisc,freedbdisc)
MB4_C_STR_GETTER(FreeDBDisc,freedbdisc,ID,id)
MB4_C_STR_GETTER(FreeDBDisc,freedbdisc,Title,title)
MB4_C_STR_GETTER(FreeDBDisc,freedbdisc,Artist,artist)
MB4_C_STR_GETTER(FreeDBDisc,freedbdisc,Category,category)
MB4_C_STR_GETTER(FreeDBDisc,freedbdisc,Year,year)
MB4_C_OBJ_GETTER(FreeDBDisc,freedbdisc,NoneMBTrackList,NoneMBTrackList)

MB4_C_DELETE(ISRC,isrc)
MB4_C_STR_GETTER(ISRC,isrc,ID,id)
MB4_C_OBJ_GETTER(ISRC,isrc,RecordingList,RecordingList)

MB4_C_DELETE(Label,label)
MB4_C_STR_GETTER(Label,label,ID,id)
MB4_C_STR_GETTER(Label,label,Type,type)
MB4_C_STR_GETTER(Label,label,Name,name)
MB4_C_STR_GETTER(Label,label,SortName,sortname)
MB4_C_STR_GETTER(Label,label,LabelCode,labelcode)
MB4_C_STR_GETTER(Label,label,Disambiguation,disambiguation)
MB4_C_STR_GETTER(Label,label,Country,country)
MB4_C_OBJ_GETTER(Label,label,Lifespan,lifespan)
MB4_C_OBJ_GETTER(Label,label,AliasList,aliaslist)
MB4_C_OBJ_GETTER(Label,label,ReleaseList,releaselist)
MB4_C_OBJ_GETTER(Label,label,RelationList,relationlist)
MB4_C_OBJ_GETTER(Label,label,TagList,taglist)
MB4_C_OBJ_GETTER(Label,label,UserTagList,usertaglist)
MB4_C_OBJ_GETTER(Label,label,Rating,rating)
MB4_C_OBJ_GETTER(Label,label,UserRating,userrating)

MB4_C_DELETE(Metadata,metadata)
MB4_C_OBJ_GETTER(Metadata,metadata,ReleaseList,releaselist)
MB4_C_OBJ_GETTER(Metadata,metadata,Disc,disc)

Mb4Query mb4_query_new(const char *Server)
{
	return new MusicBrainz4::CQuery(Server ? Server : "www.musicbrainz.org");
}

MB4_C_DELETE(Query,query)

Mb4Metadata mb4_query_query(Mb4Query Query, const char *Resource, const char *ID, int NumParams, char **ParamName, char **ParamValue)
{
	MusicBrainz4::CQuery::tParamMap Params;

	for (int count=0;count<NumParams;count++)
	{
		Params[ParamName[count]]=ParamValue[count];
	}

	MusicBrainz4::CQuery *TheQuery=reinterpret_cast<MusicBrainz4::CQuery *>(Query);
	return new MusicBrainz4::CMetadata(TheQuery->Query(Resource,ID,Params));
}

MB4_C_DELETE(Release,release)
MB4_C_STR_GETTER(Release,release,ID,id)
MB4_C_STR_GETTER(Release,release,Title,title)
MB4_C_STR_GETTER(Release,release,Status,status)
MB4_C_STR_GETTER(Release,release,Quality,quality)
MB4_C_STR_GETTER(Release,release,Disambiguation,disambiguation)
MB4_C_STR_GETTER(Release,release,Packaging,packaging)
MB4_C_OBJ_GETTER(Release,release,TextRepresentation,textrepresentation)
MB4_C_STR_GETTER(Release,release,Date,date)
MB4_C_STR_GETTER(Release,release,Country,country)
MB4_C_STR_GETTER(Release,release,Barcode,barcode)
MB4_C_STR_GETTER(Release,release,ASIN,asin)
MB4_C_OBJ_GETTER(Release,release,LabelInfoList,labelinfolist)
MB4_C_OBJ_GETTER(Release,release,MediumList,mediumlist)
MB4_C_OBJ_GETTER(Release,release,RelationList,relationlist)

MB4_C_LIST_GETTER(Alias,alias)
MB4_C_LIST_GETTER(LabelInfo,labelinfo)
MB4_C_LIST_GETTER(Label,label)
MB4_C_LIST_GETTER(Medium,medium)
MB4_C_LIST_GETTER(NameCredit,namecredit)
MB4_C_LIST_GETTER(NoneMBTrack,nonembtrack)
MB4_C_LIST_GETTER(Recording,recording)
MB4_C_LIST_GETTER(Relation,relation)
MB4_C_LIST_GETTER(Release,release)
MB4_C_LIST_GETTER(ReleaseGroup,releasegroup)
MB4_C_LIST_GETTER(Tag,tag)
MB4_C_LIST_GETTER(UserTag,usertag)
MB4_C_LIST_GETTER(Work,work)
