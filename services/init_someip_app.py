import argparse


def main(app_name, app_type):

    pass

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    
    parser.add_argument("-n", "--app-name", required=True, type=str, help="Name of the app")
    parser.add_argument("-t", "--app-type", required=True, type=str, choices=["method", "event"], help="Type of the app (method or event)")

    args = parser.parse_args()

    app_name = args.app_name
    app_type = args.app_type

    #print(f"Creating {app_type} app {app_name}")
    main(app_name, app_type)