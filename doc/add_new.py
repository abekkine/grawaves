#!/usr/bin/python

import sys

def main():

    if len(sys.argv)>1:
        add_new_item( sys.argv[1:][0] )
    else:
        add_new_item()

def read_content( filename ):
    
    try:
        f = open( filename, 'r' )
        content = f.readlines()
        f.close()
    except Exception, err:
        content = []
        pass

    # trim empty lines.
    if '\n' in content:
        content.remove( '\n' )

    return content

def save_content( filename, content ):
    f = open( filename, 'w' )
    f.writelines( content )
    f.close()

def extract_id_numbers( content ):

    statusCode = True
    statusMsg = 'OK'
    id_numbers = []
    line_no = 1
    for line in content:
        line_array = line.split( '|' )
        id_string = line_array[0]
        if len( line_array )>2:
            message = line_array[2]
            if '{TODO}' in message:
                msg = message.strip().split()
                msg.remove( '{TODO}' )
                if len( msg )==0:
                    # Unused new item exists.
                    statusMsg = 'Use existing new item.'
                    statusCode = False
                    return ( [], statusCode, statusMsg )
        else:
            # Missing message field.
            statusCode = False            
            statusMsg = 'Missing message field in todo list at line %s.' % line_no
            return ( [], statusCode, statusMsg )
        
        try:
            id_number = int( id_string, 10 )
            if id_number not in [n[0] for n in id_numbers]:
                id_numbers.append( (id_number, line_no) )
            else:
                # Duplicate id number:
                statusCode = False
                statusMsg = 'Duplicate Id Number detected.'
                return ( [], statusCode, statusMsg )
                
        except Exception, err:
            # Simply ignore the line.
            statusCode = False
            statusMsg = 'Line ignored.'
            return ( [], statusCode, statusMsg )
            pass
        line_no = line_no + 1
        
    return (id_numbers, statusCode, statusMsg)  

def get_new_id( id_numbers ):
    
    if len( id_numbers )>0:
        id_numbers.sort()
        new_number = id_numbers[-1:][0][0]+1 
    else:
        new_number = 1
        
    return new_number

def add_new_item( new_message='{TODO}' ):

    content = read_content( 'todo.txt' )

    id_numbers, code, msg = extract_id_numbers( content )

    if code:
        new_id_number = get_new_id( id_numbers )
        new_id_string = '{0:04d}'.format( new_id_number )
        new_line_text = '%s | OPEN | %s\n' % ( new_id_string, new_message )
        content.append( new_line_text )
        save_content( 'todo.txt', content )
    else:
        print msg
        sys.exit(1)

if __name__ == '__main__':
    main()


