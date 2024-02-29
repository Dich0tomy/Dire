#include <Windows.h>
#include <Knownfolders.h>
#include <Shlobj.h>

#include <dire/detail/system_dirs/windows.hpp>

#include <dire/defines.hpp>

namespace
{
auto enum_to_native_ref(dire::detail::system_dirs::KnownFolderID folder_id)
{
	switch(folder_id) {
		using enum dire::detail::system_dirs::KnownFolderID;

		case Profile: return FOLDERID_Profile; break;
		case RoamingAppData: return FOLDERID_RoamingAppData; break;
		case LocalAppData: return FOLDERID_LocalAppData; break;
		case Music: return FOLDERID_Music; break;
		case Desktop: return FOLDERID_Desktop; break;
		case Documents: return FOLDERID_Documents; break;
		case Downloads: return FOLDERID_Downloads; break;
		case Pictures: return FOLDERID_Pictures; break;
		case Public: return FOLDERID_Public; break;
		case Templates: return FOLDERID_Templates; break;
		case Videos: return FOLDERID_Videos; break;
	}
};

} // namespace

namespace dire::detail::system_dirs
{

auto known_folder(KnownFolderID folder_id, KnownFolderFlag flag, HANDLE token) -> Optional<Path>
{
	PWSTR known_folder_path = nullptr;

	auto const result = SHGetKnownFolderPath(
		enum_to_native_ref(folder_id),
		static_cast<KNOWN_FOLDER_FLAG>(flag),
		token,
		&known_folder_path
	);

	if(FAILED(result)) {
		CoTaskMemFree(known_folder_path); // Kyrie Eleison
		return {};
	}

	auto path = Path(known_folder_path);

	CoTaskMemFree(known_folder_path); // Kyrie Eleison

	return std::move(path);
}

} // namespace dire::detail::system_dirs
