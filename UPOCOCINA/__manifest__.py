# -*- coding: utf-8 -*-
{
    'name': "gym",

    'summary': """
        Sumario del modulo GYM""",

    'description': """
        Descripcion del modulo GYM
    """,

    'author': "TSI - UPO",
    'website': "http://www.yourcompany.com",

    # Categories can be used to filter modules in modules listing
    # Check https://github.com/odoo/odoo/blob/13.0/odoo/addons/base/data/ir_module_category_data.xml
    # for the full list
    'category': 'Uncategorized',
    'version': '0.1',

    # any module necessary for this one to work correctly
    'depends': ['base'],

    # always loaded
    'data': [
        'security/security.xml',
        'security/ir.model.access.csv',
        'views/classes_views.xml',
        'views/users_view.xml',
        'views/instructores_view.xml',
        'views/menu.xml',
    ],
    # only loaded in demonstration mode
    'demo': [
        'demo/demo.xml',
    ],
}
