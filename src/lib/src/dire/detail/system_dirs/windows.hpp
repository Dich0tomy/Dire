#pragma once

#include <Windows.h>
#include <Knownfolders.h>
#include <Shlobj.h>

#include <dire/defines.hpp>

namespace dire::detail::system_dirs
{

enum class KnownFolderID
{
	Profile,
	RoamingAppData,
	LocalAppData,

	Music,
	Desktop,
	Documents,
	Downloads,
	Pictures,
	Public,
	Templates,
	Videos,
};

enum class KnownFolderFlag
{
	Default = KF_FLAG_DEFAULT,
	ForceAppDataRedirection = KF_FLAG_FORCE_APP_DATA_REDIRECTION,
	ReturnFilterRedirectionTarget = KF_FLAG_RETURN_FILTER_REDIRECTION_TARGET,
	ForcePackageRedirection = KF_FLAG_FORCE_PACKAGE_REDIRECTION,
	NoPackageRedirection = KF_FLAG_NO_PACKAGE_REDIRECTION,
	ForceAppcontainerRedirection = KF_FLAG_FORCE_APPCONTAINER_REDIRECTION,
	NoAppcontainerRedirection = KF_FLAG_NO_APPCONTAINER_REDIRECTION,
	Create = KF_FLAG_CREATE,
	DontVerify = KF_FLAG_DONT_VERIFY,
	DontUnexpand = KF_FLAG_DONT_UNEXPAND,
	NoAlias = KF_FLAG_NO_ALIAS,
	Init = KF_FLAG_INIT,
	DefaultPath = KF_FLAG_DEFAULT_PATH,
	NotParentRelative = KF_FLAG_NOT_PARENT_RELATIVE,
	SimpleIdlist = KF_FLAG_SIMPLE_IDLIST,
	AliasOnly = KF_FLAG_ALIAS_ONLY,
};

auto known_folder(KnownFolderID folder_id, KnownFolderFlag flag = KnownFolderFlag::Default, HANDLE token = nullptr) -> Optional<Path>;

} // namespace dire::detail::system_dirs
