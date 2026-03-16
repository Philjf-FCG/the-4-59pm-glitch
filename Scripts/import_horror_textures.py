import os
import unreal

PROJECT_ROOT = unreal.Paths.convert_relative_path_to_full(unreal.Paths.project_dir())
SOURCE_ROOT = os.path.join(PROJECT_ROOT, 'ExternalAssets', 'SBS_Horror_512', '512x512')
DEST_ROOT = '/Game/Horror/Textures'
MATERIAL_ROOT = '/Game/Horror/Materials'

TEXTURE_MAP = {
    'Wall': 'Horror_Wall_06-512x512.png',
    'Floor': 'Horror_Floor_04-512x512.png',
    'Ceiling': 'Horror_Wall_11-512x512.png',
    'Metal': 'Horror_Metal_03-512x512.png',
    'Accent': 'Horror_Misc_05-512x512.png',
    'Stain': 'Horror_Stain_09-512x512.png',
    'Stone': 'Horror_Stone_03-512x512.png',
}

asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
editor_lib = unreal.EditorAssetLibrary
material_lib = unreal.MaterialEditingLibrary


def ensure_dir(path: str):
    if not editor_lib.does_directory_exist(path):
        editor_lib.make_directory(path)


def import_texture(src_file: str, dest_path: str):
    task = unreal.AssetImportTask()
    task.set_editor_property('filename', src_file)
    task.set_editor_property('destination_path', dest_path)
    task.set_editor_property('replace_existing', True)
    task.set_editor_property('save', True)
    task.set_editor_property('automated', True)
    task.set_editor_property('async_', False)
    asset_tools.import_asset_tasks([task])
    imported = task.get_editor_property('imported_object_paths')
    return imported[0] if imported else None


def create_surface_material(mat_name: str, texture_asset_path: str, roughness: float, metallic: float = 0.0):
    mat_path = f'{MATERIAL_ROOT}/{mat_name}'
    if editor_lib.does_asset_exist(mat_path):
        editor_lib.delete_asset(mat_path)

    material = asset_tools.create_asset(mat_name, MATERIAL_ROOT, unreal.Material, unreal.MaterialFactoryNew())
    texture = editor_lib.load_asset(texture_asset_path)

    tex_node = material_lib.create_material_expression(material, unreal.MaterialExpressionTextureSampleParameter2D, -420, -120)
    tex_node.set_editor_property('parameter_name', 'BaseColorTex')
    tex_node.texture = texture
    material_lib.connect_material_property(tex_node, 'RGB', unreal.MaterialProperty.MP_BASE_COLOR)

    rough_node = material_lib.create_material_expression(material, unreal.MaterialExpressionConstant, -420, 70)
    rough_node.set_editor_property('r', roughness)
    material_lib.connect_material_property(rough_node, '', unreal.MaterialProperty.MP_ROUGHNESS)

    metallic_node = material_lib.create_material_expression(material, unreal.MaterialExpressionConstant, -420, 150)
    metallic_node.set_editor_property('r', metallic)
    material_lib.connect_material_property(metallic_node, '', unreal.MaterialProperty.MP_METALLIC)

    spec_node = material_lib.create_material_expression(material, unreal.MaterialExpressionConstant, -420, 230)
    spec_node.set_editor_property('r', 0.15)
    material_lib.connect_material_property(spec_node, '', unreal.MaterialProperty.MP_SPECULAR)

    material_lib.layout_material_expressions(material)
    material_lib.recompile_material(material)
    editor_lib.save_loaded_asset(material)
    return mat_path


ensure_dir(DEST_ROOT)
ensure_dir(MATERIAL_ROOT)

imported_assets = {}
for category, filename in TEXTURE_MAP.items():
    if category == 'Accent':
        folder = 'Misc'
    elif category == 'Ceiling':
        folder = 'Wall'
    elif category == 'Stain':
        folder = 'Stains'
    else:
        folder = category

    src_path = os.path.join(SOURCE_ROOT, folder, filename)
    imported_path = import_texture(src_path, DEST_ROOT)
    if imported_path:
        imported_assets[category] = imported_path

created_materials = {}
if 'Wall' in imported_assets:
    created_materials['Wall'] = create_surface_material('M_HorrorWall', imported_assets['Wall'], 0.92)
if 'Ceiling' in imported_assets:
    created_materials['Ceiling'] = create_surface_material('M_HorrorCeiling', imported_assets['Ceiling'], 0.96)
if 'Floor' in imported_assets:
    created_materials['Floor'] = create_surface_material('M_HorrorFloor', imported_assets['Floor'], 0.82)
if 'Metal' in imported_assets:
    created_materials['Metal'] = create_surface_material('M_HorrorMetal', imported_assets['Metal'], 0.48, 0.15)
if 'Accent' in imported_assets:
    created_materials['Accent'] = create_surface_material('M_HorrorAccent', imported_assets['Accent'], 0.65)
if 'Stain' in imported_assets:
    created_materials['Stain'] = create_surface_material('M_HorrorStain', imported_assets['Stain'], 0.88)
if 'Stone' in imported_assets:
    created_materials['Stone'] = create_surface_material('M_HorrorStone', imported_assets['Stone'], 0.9)

unreal.log('Imported textures: {}'.format(imported_assets))
unreal.log('Created materials: {}'.format(created_materials))
